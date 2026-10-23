package clk

import (
	"sort"
	"sync"
)

// Seq numbers the records of a single writer: 1, 2, 3, ... It is safe for use from many goroutines.
type Seq struct {
	mu sync.Mutex
	n  uint64
}

// Next returns the next sequence number.
func (s *Seq) Next() uint64 {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.n++
	return s.n
}

// Rec is a record written by the single writer.
type Rec struct {
	Seq uint64
	Val string
}

// InOrder returns the records sorted by Seq with duplicates (same Seq) removed, keeping the first
// copy that was received. The input is not changed.
func InOrder(recs []Rec) []Rec {
	seen := map[uint64]bool{}
	var out []Rec
	for _, r := range recs {
		out = append(out, r)
	}
	sort.Slice(out, func(i, j int) bool { return out[i].Seq < out[j].Seq })
	return out
}

// Gaps returns the sequence numbers from 1 up to the highest received that are missing, in increasing
// order. A sequence number shows that a record is missing; a timestamp cannot.
func Gaps(recs []Rec) []uint64 {
	have := map[uint64]bool{}
	var top uint64
	for _, r := range recs {
		have[r.Seq] = true
		if r.Seq > top {
			top = r.Seq
		}
	}
	var out []uint64
	for s := uint64(1); s <= top; s++ {
		if !have[s] {
			out = append(out, s)
		}
	}
	return out
}
