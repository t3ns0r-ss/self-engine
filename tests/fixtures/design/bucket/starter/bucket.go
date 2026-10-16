// Package ratelimit: implement a token bucket (see README.md).
package ratelimit

import "time"

type Bucket struct{}

// New returns a bucket that refills at rate tokens per second, holds at most burst tokens,
// starts full, and reads the time from now (tests pass a fake clock).
func New(rate float64, burst int, now func() time.Time) *Bucket { panic("not implemented") }

// Allow takes one token if one is available and reports whether it did. Safe for concurrent use.
func (b *Bucket) Allow() bool { panic("not implemented") }
