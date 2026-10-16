package main

import (
	"context"
	"net/http"
	"net/http/httptest"
	"sync"
	"sync/atomic"
	"testing"
	"time"
)

func TestPercentile(t *testing.T) {
	s := []float64{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	if Percentile(s, 50) != 5 || Percentile(s, 90) != 9 || Percentile(s, 100) != 10 || Percentile(s, 1) != 1 {
		t.Fatalf("nearest-rank percentiles wrong: %v %v %v", Percentile(s, 50), Percentile(s, 90), Percentile(s, 100))
	}
	if Percentile(nil, 50) != 0 {
		t.Fatal("empty input")
	}
}

func TestMedianNearServiceTime(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		time.Sleep(10 * time.Millisecond)
	}))
	defer srv.Close()
	r := Run(context.Background(), Config{URL: srv.URL, Rate: 50, Duration: 2 * time.Second, Seed: 1})
	if r.OK < 90 || r.Errors != 0 {
		t.Fatalf("ok=%d errors=%d, want about 100 ok", r.OK, r.Errors)
	}
	if r.P50 < 0.010 || r.P50 > 0.030 {
		t.Fatalf("p50 = %.1f ms, want 10-30 ms for a 10 ms server on loopback", r.P50*1e3)
	}
}

// A server that stalls once for 1 s: the open loop keeps scheduling requests and shows many slow ones;
// the closed loop waits and records a single slow request.
func TestOpenLoopSeesStallClosedLoopHidesIt(t *testing.T) {
	newStalling := func() *httptest.Server {
		// A single-threaded server: every request takes the lock, so one stall delays all that arrive meanwhile.
		var n atomic.Int32
		var mu sync.Mutex
		return httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
			mu.Lock()
			defer mu.Unlock()
			if n.Add(1) == 20 {
				time.Sleep(time.Second)
			}
		}))
	}
	a := newStalling()
	defer a.Close()
	open := Run(context.Background(), Config{URL: a.URL, Rate: 100, Duration: 3 * time.Second, Seed: 1})
	b := newStalling()
	defer b.Close()
	closed := Run(context.Background(), Config{URL: b.URL, Closed: true, Workers: 1, Duration: 3 * time.Second})
	if open.P99 < 0.3 {
		t.Fatalf("open-loop p99 = %.0f ms, want a large value caused by the stall", open.P99*1e3)
	}
	if closed.P99 > open.P99/3 {
		t.Fatalf("closed-loop p99 %.0f ms should be much smaller than open-loop p99 %.0f ms", closed.P99*1e3, open.P99*1e3)
	}
}

func TestTimeoutsAreCounted(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		time.Sleep(300 * time.Millisecond)
	}))
	defer srv.Close()
	r := Run(context.Background(), Config{URL: srv.URL, Rate: 20, Duration: time.Second, Timeout: 50 * time.Millisecond, Seed: 1})
	if r.Timeouts == 0 || r.OK != 0 {
		t.Fatalf("timeouts=%d ok=%d, want all timeouts", r.Timeouts, r.OK)
	}
}
