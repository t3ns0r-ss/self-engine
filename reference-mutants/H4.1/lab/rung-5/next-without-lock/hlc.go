package clk

import (
	"sync"
	"time"
)

// Clock is a source of wall-clock time. Tests supply a fake one.
type Clock interface{ Now() time.Time }

// HLCTime is a hybrid logical timestamp: a physical part in nanoseconds and a counter for ties.
type HLCTime struct {
	L int64
	C uint32
}

// Less is the total order on hybrid timestamps: by L, then by C.
func (a HLCTime) Less(b HLCTime) bool { return a.L < b.L || (a.L == b.L && a.C < b.C) }

// HLC is a hybrid logical clock. It follows the physical clock when that moves forward and
// uses the counter otherwise, so its timestamps never go backwards and a receive is always
// after the send that caused it, even when the two machines' clocks disagree.
type HLC struct {
	mu    sync.Mutex
	clock Clock
	last  HLCTime
}

func NewHLC(c Clock) *HLC { return &HLC{clock: c} }

// Now stamps a local or send event: the physical time if it is ahead of the last stamp,
// otherwise the last stamp with the counter increased.
func (h *HLC) Now() HLCTime {
	h.mu.Lock()
	defer h.mu.Unlock()
	pt := h.clock.Now().UnixNano()
	if pt > h.last.L {
		h.last = HLCTime{pt, 0}
	} else {
		h.last.C++
	}
	return h.last
}

// Receive stamps the receipt of a message that carried m. The result is after both the last
// local stamp and m.
func (h *HLC) Receive(m HLCTime) HLCTime {
	h.mu.Lock()
	defer h.mu.Unlock()
	pt := h.clock.Now().UnixNano()
	l := max(h.last.L, m.L, pt)
	var c uint32
	switch {
	case l == h.last.L && l == m.L:
		c = max(h.last.C, m.C) + 1
	case l == h.last.L:
		c = h.last.C + 1
	case l == m.L:
		c = m.C + 1
	}
	h.last = HLCTime{l, c}
	return h.last
}
