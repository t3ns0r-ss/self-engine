// Package ratelimit is a token bucket: tokens refill continuously at a fixed rate up to a cap (burst),
// and each allowed request spends one token.
package ratelimit

import (
	"sync"
	"time"
)

type Bucket struct {
	mu     sync.Mutex
	rate   float64 // tokens per second
	burst  float64 // capacity
	tokens float64 // current tokens, fractional so slow refills are not lost
	last   time.Time
	now    func() time.Time
}

func New(rate float64, burst int, now func() time.Time) *Bucket {
	return &Bucket{rate: rate, burst: float64(burst), tokens: float64(burst), last: now(), now: now}
}

func (b *Bucket) Allow() bool {
	b.mu.Lock()
	defer b.mu.Unlock()
	t := b.now()
	b.tokens += t.Sub(b.last).Seconds() * b.rate
	if b.tokens > b.burst {
		b.tokens = b.burst
	}
	b.last = t
	if b.tokens >= 1 {
		b.tokens--
		return true
	}
	return false
}
