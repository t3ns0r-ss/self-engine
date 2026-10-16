package main

import (
	"bufio"
	"net"
	"net/http"
	"net/http/httptest"
	"testing"
	"time"
)

// echoServer replies to each line with the same line.
func echoServer(t *testing.T) string {
	t.Helper()
	l, err := net.Listen("tcp", "127.0.0.1:0")
	if err != nil {
		t.Fatal(err)
	}
	t.Cleanup(func() { l.Close() })
	go func() {
		for {
			c, err := l.Accept()
			if err != nil {
				return
			}
			go func() {
				defer c.Close()
				r := bufio.NewReader(c)
				for {
					s, err := r.ReadString('\n')
					if err != nil {
						return
					}
					c.Write([]byte(s))
				}
			}()
		}
	}()
	return l.Addr().String()
}

func startProxy(t *testing.T, upstream string) (*Proxy, string) {
	t.Helper()
	p := NewProxy(upstream, 1)
	l, err := net.Listen("tcp", "127.0.0.1:0")
	if err != nil {
		t.Fatal(err)
	}
	go p.Serve(l)
	t.Cleanup(p.Close)
	return p, l.Addr().String()
}

// roundTrip dials addr, sends one line, and returns the elapsed time or an error (deadline: 1 s).
func roundTrip(addr string, deadline time.Duration) (time.Duration, error) {
	start := time.Now()
	c, err := net.DialTimeout("tcp", addr, deadline)
	if err != nil {
		return 0, err
	}
	defer c.Close()
	c.SetDeadline(time.Now().Add(deadline))
	if _, err := c.Write([]byte("hi\n")); err != nil {
		return 0, err
	}
	if _, err := bufio.NewReader(c).ReadString('\n'); err != nil {
		return 0, err
	}
	return time.Since(start), nil
}

func TestDelayIsAtLeastRequested(t *testing.T) {
	p, addr := startProxy(t, echoServer(t))
	if _, err := roundTrip(addr, time.Second); err != nil {
		t.Fatalf("normal call failed: %v", err)
	}
	p.SetDelay(200*time.Millisecond, 0)
	d, err := roundTrip(addr, 2*time.Second)
	if err != nil {
		t.Fatal(err)
	}
	if d < 200*time.Millisecond {
		t.Fatalf("delayed call took %v, want at least 200ms", d)
	}
}

func TestBlackholeTimesOutAndHealRestores(t *testing.T) {
	p, addr := startProxy(t, echoServer(t))
	p.SetBlackhole(true)
	start := time.Now()
	if _, err := roundTrip(addr, 300*time.Millisecond); err == nil {
		t.Fatal("blackholed call succeeded")
	}
	if el := time.Since(start); el < 250*time.Millisecond || el > 2*time.Second {
		t.Fatalf("blackholed call ended after %v, want about the 300ms deadline", el)
	}
	p.Heal()
	if _, err := roundTrip(addr, time.Second); err != nil {
		t.Fatalf("after heal: %v", err)
	}
}

func TestDropAllAndControlInterface(t *testing.T) {
	p, addr := startProxy(t, echoServer(t))
	srv := httptest.NewServer(p.ControlHandler())
	defer srv.Close()
	post := func(path string) int {
		r, err := http.Post(srv.URL+path, "", nil)
		if err != nil {
			t.Fatal(err)
		}
		r.Body.Close()
		return r.StatusCode
	}
	if post("/drop?p=1") != 200 {
		t.Fatal("/drop failed")
	}
	if _, err := roundTrip(addr, 500*time.Millisecond); err == nil {
		t.Fatal("call succeeded with drop probability 1")
	}
	if post("/drop?p=7") != 400 {
		t.Fatal("/drop?p=7 should be rejected")
	}
	if post("/heal") != 200 {
		t.Fatal("/heal failed")
	}
	if _, err := roundTrip(addr, time.Second); err != nil {
		t.Fatalf("after heal: %v", err)
	}
	if post("/close-all") != 200 {
		t.Fatal("/close-all failed")
	}
}
