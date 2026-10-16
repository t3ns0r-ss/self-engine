// Command loadgen is an open-loop HTTP load generator.
//
//	go run ./shared/go/loadgen -url http://127.0.0.1:8080/ -rate 200 -duration 10s [-poisson -seed 1] [-raw lat.txt]
//
// Open loop: request i is sent at its scheduled time whether or not earlier requests have returned, and its
// latency is measured from that scheduled time. A server that stalls therefore shows up as many slow
// requests, instead of being hidden because the generator waited (coordinated omission).
// -closed switches to a closed loop (N workers, each sending when its last request returned); it exists
// only to show the difference (H0.1).
package main

import (
	"context"
	"flag"
	"fmt"
	"io"
	"math/rand"
	"net/http"
	"os"
	"sort"
	"sync"
	"time"
)

// Config describes one run.
type Config struct {
	URL      string
	Rate     float64       // requests per second (open loop)
	Duration time.Duration // how long to schedule requests
	Poisson  bool          // exponential gaps between requests instead of fixed gaps
	Seed     int64
	Timeout  time.Duration // per request, measured from the scheduled time
	Closed   bool
	Workers  int // closed loop only
}

// Result summarises a run. Latencies are in seconds, in the order the requests completed.
type Result struct {
	Sent, OK, Errors, Timeouts int
	AchievedRate               float64
	Latencies                  []float64
	P50, P90, P99, P999, Max   float64
}

// Percentile returns the p-th percentile (0 < p <= 100) of sorted, by the nearest-rank method.
func Percentile(sorted []float64, p float64) float64 {
	if len(sorted) == 0 {
		return 0
	}
	rank := int(float64(len(sorted))*p/100 + 0.999999999)
	if rank < 1 {
		rank = 1
	}
	if rank > len(sorted) {
		rank = len(sorted)
	}
	return sorted[rank-1]
}

// Run executes the load and returns its summary.
func Run(ctx context.Context, cfg Config) Result {
	tr := &http.Transport{MaxIdleConnsPerHost: 1024, MaxConnsPerHost: 0}
	client := &http.Client{Transport: tr}
	defer tr.CloseIdleConnections()
	if cfg.Timeout <= 0 {
		cfg.Timeout = 5 * time.Second
	}

	var mu sync.Mutex
	var res Result
	record := func(scheduled time.Time, err error, status int) {
		lat := time.Since(scheduled).Seconds()
		mu.Lock()
		defer mu.Unlock()
		res.Sent++
		switch {
		case err != nil && ctx.Err() == nil && isTimeout(err):
			res.Timeouts++
		case err != nil || status >= 500:
			res.Errors++
		default:
			res.OK++
		}
		res.Latencies = append(res.Latencies, lat)
	}
	one := func(scheduled time.Time) {
		rctx, cancel := context.WithDeadline(ctx, scheduled.Add(cfg.Timeout))
		defer cancel()
		req, _ := http.NewRequestWithContext(rctx, http.MethodGet, cfg.URL, nil)
		resp, err := client.Do(req)
		status := 0
		if err == nil {
			status = resp.StatusCode
			io.Copy(io.Discard, resp.Body)
			resp.Body.Close()
		}
		record(scheduled, err, status)
	}

	start := time.Now()
	var wg sync.WaitGroup
	if cfg.Closed {
		n := cfg.Workers
		if n < 1 {
			n = 1
		}
		for w := 0; w < n; w++ {
			wg.Add(1)
			go func() {
				defer wg.Done()
				for time.Since(start) < cfg.Duration && ctx.Err() == nil {
					one(time.Now()) // closed loop: "scheduled" is simply when this request was sent
				}
			}()
		}
	} else {
		rng := rand.New(rand.NewSource(cfg.Seed))
		gap := time.Duration(float64(time.Second) / cfg.Rate)
		next := start
		for ctx.Err() == nil && next.Sub(start) < cfg.Duration {
			if d := time.Until(next); d > 0 {
				time.Sleep(d)
			}
			wg.Add(1)
			go func(s time.Time) { defer wg.Done(); one(s) }(next)
			if cfg.Poisson {
				next = next.Add(time.Duration(rng.ExpFloat64() * float64(gap)))
			} else {
				next = next.Add(gap)
			}
		}
	}
	wg.Wait()
	elapsed := time.Since(start).Seconds()
	if elapsed > 0 {
		res.AchievedRate = float64(res.OK) / elapsed
	}
	sorted := append([]float64(nil), res.Latencies...)
	sort.Float64s(sorted)
	res.P50, res.P90, res.P99, res.P999 = Percentile(sorted, 50), Percentile(sorted, 90), Percentile(sorted, 99), Percentile(sorted, 99.9)
	if len(sorted) > 0 {
		res.Max = sorted[len(sorted)-1]
	}
	return res
}

func isTimeout(err error) bool {
	type timeout interface{ Timeout() bool }
	if t, ok := err.(timeout); ok && t.Timeout() {
		return true
	}
	return err != nil && (err == context.DeadlineExceeded || containsDeadline(err.Error()))
}

func containsDeadline(s string) bool {
	for _, k := range []string{"deadline exceeded", "timeout"} {
		for i := 0; i+len(k) <= len(s); i++ {
			if s[i:i+len(k)] == k {
				return true
			}
		}
	}
	return false
}

// Summary renders the TSV summary (header line, then one data line).
func (r Result) Summary() string {
	return fmt.Sprintf("sent\tok\terrors\ttimeouts\tachieved_rate\tp50_ms\tp90_ms\tp99_ms\tp999_ms\tmax_ms\n"+
		"%d\t%d\t%d\t%d\t%.1f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
		r.Sent, r.OK, r.Errors, r.Timeouts, r.AchievedRate, r.P50*1e3, r.P90*1e3, r.P99*1e3, r.P999*1e3, r.Max*1e3)
}

func main() {
	url := flag.String("url", "", "target URL (required)")
	rate := flag.Float64("rate", 100, "requests per second (open loop)")
	dur := flag.Duration("duration", 10*time.Second, "how long to send")
	poisson := flag.Bool("poisson", false, "seeded Poisson arrivals instead of a fixed gap")
	seed := flag.Int64("seed", 1, "seed for Poisson arrivals")
	timeout := flag.Duration("timeout", 5*time.Second, "per-request timeout, from the scheduled time")
	closed := flag.Bool("closed", false, "closed loop (only for comparisons)")
	workers := flag.Int("workers", 1, "closed loop: number of workers")
	raw := flag.String("raw", "", "write every latency (seconds), one per line, to this file")
	flag.Parse()
	if *url == "" {
		fmt.Fprintln(os.Stderr, "loadgen: -url is required")
		os.Exit(2)
	}
	r := Run(context.Background(), Config{URL: *url, Rate: *rate, Duration: *dur, Poisson: *poisson, Seed: *seed, Timeout: *timeout, Closed: *closed, Workers: *workers})
	fmt.Print(r.Summary())
	if *raw != "" {
		f, err := os.Create(*raw)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
		defer f.Close()
		for _, l := range r.Latencies {
			fmt.Fprintf(f, "%.6f\n", l)
		}
	}
}
