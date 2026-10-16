// Command faultproxy is a TCP proxy that sits between two processes and injects faults on demand.
//
//	go run ./shared/go/faultproxy -listen :7001 -upstream 127.0.0.1:8001 -control :9001 -seed 1
//
// Control, by HTTP on the control port:
//
//	POST /delay?ms=200&jitter=50   add 200 ms (plus 0-50 ms, seeded) before each new connection is forwarded
//	POST /drop?p=0.1               close new connections with probability p
//	POST /blackhole                accept connections and never forward them, so callers hit their timeouts
//	POST /heal                     back to normal
//	POST /close-all                close every open connection now
package main

import (
	"flag"
	"fmt"
	"io"
	"log"
	"math/rand"
	"net"
	"net/http"
	"strconv"
	"sync"
	"time"
)

// Proxy forwards TCP connections from a listener to an upstream address, subject to the current fault.
type Proxy struct {
	upstream string

	mu        sync.Mutex
	rng       *rand.Rand
	delay     time.Duration
	jitter    time.Duration
	dropP     float64
	blackhole bool
	conns     map[net.Conn]struct{}
	closed    bool
	stop      chan struct{}
}

// NewProxy creates a proxy to upstream. The seed fixes the sequence of jitter and drop decisions.
func NewProxy(upstream string, seed int64) *Proxy {
	return &Proxy{upstream: upstream, rng: rand.New(rand.NewSource(seed)), conns: map[net.Conn]struct{}{}, stop: make(chan struct{})}
}

func (p *Proxy) SetDelay(d, jitter time.Duration) {
	p.mu.Lock()
	p.delay, p.jitter = d, jitter
	p.mu.Unlock()
}
func (p *Proxy) SetDrop(prob float64) { p.mu.Lock(); p.dropP = prob; p.mu.Unlock() }
func (p *Proxy) SetBlackhole(b bool)  { p.mu.Lock(); p.blackhole = b; p.mu.Unlock() }

// Heal removes every injected fault.
func (p *Proxy) Heal() {
	p.mu.Lock()
	p.delay, p.jitter, p.dropP, p.blackhole = 0, 0, 0, false
	p.mu.Unlock()
}

// CloseAll closes every open connection.
func (p *Proxy) CloseAll() {
	p.mu.Lock()
	for c := range p.conns {
		c.Close()
	}
	p.mu.Unlock()
}

// Close stops the proxy and closes every connection.
func (p *Proxy) Close() {
	p.mu.Lock()
	if !p.closed {
		p.closed = true
		close(p.stop)
	}
	p.mu.Unlock()
	p.CloseAll()
}

func (p *Proxy) track(c net.Conn) bool {
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.closed {
		return false
	}
	p.conns[c] = struct{}{}
	return true
}

func (p *Proxy) untrack(c net.Conn) {
	p.mu.Lock()
	delete(p.conns, c)
	p.mu.Unlock()
	c.Close()
}

// Serve accepts connections on l until l is closed or the proxy is closed.
func (p *Proxy) Serve(l net.Listener) {
	go func() { <-p.stop; l.Close() }()
	for {
		c, err := l.Accept()
		if err != nil {
			return
		}
		go p.handle(c)
	}
}

func (p *Proxy) handle(client net.Conn) {
	if !p.track(client) {
		client.Close()
		return
	}
	defer p.untrack(client)

	p.mu.Lock()
	delay, jitter, dropP, hole := p.delay, p.jitter, p.dropP, p.blackhole
	drop := dropP > 0 && p.rng.Float64() < dropP
	if jitter > 0 {
		delay += time.Duration(p.rng.Int63n(int64(jitter) + 1))
	}
	p.mu.Unlock()

	if drop {
		return
	}
	if hole {
		// Hold the connection open and forward nothing: the caller's own deadline ends the call.
		io.Copy(io.Discard, client)
		return
	}
	if delay > 0 {
		select {
		case <-time.After(delay):
		case <-p.stop:
			return
		}
	}
	up, err := net.DialTimeout("tcp", p.upstream, 2*time.Second)
	if err != nil {
		return
	}
	if !p.track(up) {
		up.Close()
		return
	}
	defer p.untrack(up)
	done := make(chan struct{}, 2)
	go func() { io.Copy(up, client); done <- struct{}{} }()
	go func() { io.Copy(client, up); done <- struct{}{} }()
	<-done // either side closing ends the exchange; the deferred untrack closes both
}

// ControlHandler is the HTTP control interface.
func (p *Proxy) ControlHandler() http.Handler {
	mux := http.NewServeMux()
	num := func(r *http.Request, k string) int {
		v, _ := strconv.Atoi(r.URL.Query().Get(k))
		return v
	}
	mux.HandleFunc("POST /delay", func(w http.ResponseWriter, r *http.Request) {
		p.SetDelay(time.Duration(num(r, "ms"))*time.Millisecond, time.Duration(num(r, "jitter"))*time.Millisecond)
		fmt.Fprintln(w, "ok")
	})
	mux.HandleFunc("POST /drop", func(w http.ResponseWriter, r *http.Request) {
		v, err := strconv.ParseFloat(r.URL.Query().Get("p"), 64)
		if err != nil || v < 0 || v > 1 {
			http.Error(w, "p must be a number from 0 to 1", http.StatusBadRequest)
			return
		}
		p.SetDrop(v)
		fmt.Fprintln(w, "ok")
	})
	mux.HandleFunc("POST /blackhole", func(w http.ResponseWriter, r *http.Request) { p.SetBlackhole(true); fmt.Fprintln(w, "ok") })
	mux.HandleFunc("POST /heal", func(w http.ResponseWriter, r *http.Request) { p.Heal(); fmt.Fprintln(w, "ok") })
	mux.HandleFunc("POST /close-all", func(w http.ResponseWriter, r *http.Request) { p.CloseAll(); fmt.Fprintln(w, "ok") })
	return mux
}

func main() {
	listen := flag.String("listen", ":7001", "address to accept connections on")
	upstream := flag.String("upstream", "127.0.0.1:8001", "address to forward to")
	control := flag.String("control", ":9001", "address of the HTTP control interface")
	seed := flag.Int64("seed", 1, "seed for jitter and drop decisions")
	flag.Parse()
	p := NewProxy(*upstream, *seed)
	l, err := net.Listen("tcp", *listen)
	if err != nil {
		log.Fatal(err)
	}
	log.Printf("faultproxy: %s -> %s, control %s, seed %d", *listen, *upstream, *control, *seed)
	go p.Serve(l)
	log.Fatal(http.ListenAndServe(*control, p.ControlHandler()))
}
