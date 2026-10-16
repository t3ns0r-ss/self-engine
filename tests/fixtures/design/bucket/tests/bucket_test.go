package ratelimit

import (
	"sync"
	"sync/atomic"
	"testing"
	"time"
)

// fakeClock lets a test move time forward by hand.
type fakeClock struct {
	mu sync.Mutex
	t  time.Time
}

func (c *fakeClock) Now() time.Time { c.mu.Lock(); defer c.mu.Unlock(); return c.t }
func (c *fakeClock) Advance(d time.Duration) { c.mu.Lock(); c.t = c.t.Add(d); c.mu.Unlock() }

func TestStartsFullThenDenies(t *testing.T) {
	c := &fakeClock{t: time.Unix(0, 0)}
	b := New(1, 3, c.Now)
	for i := 0; i < 3; i++ {
		if !b.Allow() {
			t.Fatalf("request %d denied; want the first 3 allowed", i+1)
		}
	}
	if b.Allow() {
		t.Fatal("4th request allowed; want denied")
	}
}

func TestRefillsAtRate(t *testing.T) {
	c := &fakeClock{t: time.Unix(0, 0)}
	b := New(2, 1, c.Now) // 2 tokens per second
	b.Allow()
	c.Advance(400 * time.Millisecond) // 0.8 tokens
	if b.Allow() {
		t.Fatal("allowed after 0.4s; want denied")
	}
	c.Advance(100 * time.Millisecond) // 0.8 + 0.2 = 1.0 token: fractions must not be lost
	if !b.Allow() {
		t.Fatal("denied after 0.5s in total; want allowed")
	}
}

func TestIdleNeverExceedsBurst(t *testing.T) {
	c := &fakeClock{t: time.Unix(0, 0)}
	b := New(10, 2, c.Now)
	c.Advance(time.Hour)
	n := 0
	for b.Allow() {
		n++
	}
	if n != 2 {
		t.Fatalf("allowed %d after a long idle; want 2 (the burst)", n)
	}
}

func TestConcurrentCallersShareTokens(t *testing.T) {
	c := &fakeClock{t: time.Unix(0, 0)}
	b := New(1, 100, c.Now)
	var allowed atomic.Int64
	var wg sync.WaitGroup
	for i := 0; i < 400; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			if b.Allow() {
				allowed.Add(1)
			}
		}()
	}
	wg.Wait()
	if got := allowed.Load(); got != 100 {
		t.Fatalf("allowed %d; want exactly 100", got)
	}
}
