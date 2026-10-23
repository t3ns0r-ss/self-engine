// Package clocks is the H4.1 lab: Lamport clocks, vector clocks, a hybrid logical clock, and a
// Process that stamps events and messages. It runs on simnet's asynchronous network in tests and
// over HTTP in cmd/node.
package clocks

import (
	"fmt"
	"sort"
	"strings"
	"sync"
	"time"
)

// Lamport is a logical clock: one counter per process.
// Rule: a local or send event adds 1; a receive sets the counter to max(own, received) + 1.
type Lamport struct {
	mu sync.Mutex
	t  uint64
}

// LamportAt returns a clock that continues from t, for a process that restarts from saved state.
func LamportAt(t uint64) *Lamport { return &Lamport{t: t} }

// Tick records a local event and returns its timestamp.
func (l *Lamport) Tick() uint64 {
	l.mu.Lock()
	defer l.mu.Unlock()
	l.t++
	return l.t
}

// Send records a send event; the returned timestamp travels with the message.
func (l *Lamport) Send() uint64 { return l.Tick() }

// Receive records the receipt of a message stamped remote.
func (l *Lamport) Receive(remote uint64) uint64 {
	l.mu.Lock()
	defer l.mu.Unlock()
	if remote > l.t {
		l.t = remote
	}
	l.t++
	return l.t
}

// Time returns the current counter without recording an event.
func (l *Lamport) Time() uint64 {
	l.mu.Lock()
	defer l.mu.Unlock()
	return l.t
}

// VC is a vector clock: one counter per process that has had an event. A missing entry means 0.
// The methods never change their receiver, so a VC that was sent in a message can be shared.
type VC map[string]uint64

// Order is the relation between two vector clocks.
type Order int

const (
	Equal      Order = iota // same events seen
	Before                  // a happened before b
	After                   // b happened before a
	Concurrent              // neither saw the other
)

func (o Order) String() string { return [...]string{"equal", "before", "after", "concurrent"}[o] }

// Inc returns a copy of v with id's entry increased by one.
func (v VC) Inc(id string) VC {
	out := v.Copy()
	out[id]++
	return out
}

// Copy returns an independent copy.
func (v VC) Copy() VC {
	out := make(VC, len(v))
	for k, n := range v {
		out[k] = n
	}
	return out
}

// Merge returns the entry-wise maximum of a and b.
func Merge(a, b VC) VC {
	out := a.Copy()
	for k, n := range b {
		if n > out[k] {
			out[k] = n
		}
	}
	return out
}

// Compare says how a and b are ordered: a is Before b when every entry of a is at most the
// matching entry of b and at least one is smaller; Concurrent when each has an entry the other lacks.
func Compare(a, b VC) Order {
	aLess, bLess := false, false
	for k, n := range a {
		if n > b[k] {
			bLess = true
		}
	}
	for k, n := range b {
		if n > a[k] {
			aLess = true
		}
	}
	switch {
	case aLess && bLess:
		return Concurrent
	case aLess:
		return Before
	case bLess:
		return After
	}
	return Equal
}

// Bytes is the size of the counters when each is sent as 8 bytes (ids not counted).
func (v VC) Bytes() int { return 8 * len(v) }

func (v VC) String() string {
	keys := make([]string, 0, len(v))
	for k := range v {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	parts := make([]string, len(keys))
	for i, k := range keys {
		parts[i] = fmt.Sprintf("%s:%d", k, v[k])
	}
	return "{" + strings.Join(parts, " ") + "}"
}

// Msg is what a Process sends: the payload and both stamps.
type Msg struct {
	Payload string
	L       uint64
	V       VC
}

// Stamp is one recorded event with both clocks.
type Stamp struct {
	Proc, Label string
	L           uint64
	V           VC
}

// Sender is the part of the network a Process needs. simnet.AsyncNet implements it.
type Sender interface {
	Send(from, to string, msg any)
}

// Process is a node that stamps every event with a Lamport time and a vector clock.
type Process struct {
	ID  string
	net Sender
	mu  sync.Mutex
	lam Lamport
	vc  VC
	log []Stamp
}

func NewProcess(id string, net Sender) *Process {
	return &Process{ID: id, net: net, vc: VC{}}
}

// Local records an event that involves no message.
func (p *Process) Local(label string) Stamp {
	p.mu.Lock()
	defer p.mu.Unlock()
	return p.record(label, p.lam.Tick(), p.vc.Inc(p.ID))
}

// SendTo records a send event and queues the message on the network.
func (p *Process) SendTo(to, payload string) Stamp {
	p.mu.Lock()
	l, v := p.lam.Send(), p.vc.Inc(p.ID)
	s := p.record("send "+payload, l, v)
	p.mu.Unlock()
	p.net.Send(p.ID, to, Msg{Payload: payload, L: l, V: v.Copy()})
	return s
}

// Handle receives a message. Register it on the network: net.Register(id, p.Handle).
func (p *Process) Handle(_ string, msg any) {
	m, ok := msg.(Msg)
	if !ok {
		return
	}
	p.mu.Lock()
	defer p.mu.Unlock()
	p.record("recv "+m.Payload, p.lam.Receive(m.L), Merge(p.vc, m.V).Inc(p.ID))
}

// record stores the stamp; the caller holds p.mu.
func (p *Process) record(label string, l uint64, v VC) Stamp {
	p.vc = v
	p.log = append(p.log, Stamp{p.ID, label, l, v.Copy()})
	return Stamp{p.ID, label, l, v.Copy()} // the caller gets its own copy
}

// Log returns the events recorded so far, in the order they happened at this process.
func (p *Process) Log() []Stamp {
	p.mu.Lock()
	defer p.mu.Unlock()
	out := make([]Stamp, len(p.log))
	for i, s := range p.log {
		out[i] = Stamp{s.Proc, s.Label, s.L, s.V.Copy()}
	}
	return out
}

// Clock is the time source for wall-clock and hybrid timestamps (simnet.Clock has the same method).
type Clock interface{ Now() time.Time }

// SkewedClock reads another clock and adds a fixed offset: a machine whose clock is wrong.
type SkewedClock struct {
	Base   Clock
	Offset time.Duration
}

func (c SkewedClock) Now() time.Time { return c.Base.Now().Add(c.Offset) }

// WallValue is a value stamped with the writer's wall-clock reading.
type WallValue struct {
	Value string
	TS    time.Time
}

// WallRegister keeps the write with the highest wall-clock timestamp (last write wins).
// It is the simple design that the happened-before card warns against.
type WallRegister struct {
	mu  sync.Mutex
	cur WallValue
}

// Write stamps value with the writer's clock and keeps it if its timestamp is the highest so far.
func (r *WallRegister) Write(c Clock, value string) WallValue {
	w := WallValue{value, c.Now()}
	r.mu.Lock()
	defer r.mu.Unlock()
	if w.TS.After(r.cur.TS) {
		r.cur = w
	}
	return w
}

func (r *WallRegister) Read() WallValue {
	r.mu.Lock()
	defer r.mu.Unlock()
	return r.cur
}

// HLCTime is a hybrid logical timestamp: a physical part in nanoseconds and a counter for ties.
type HLCTime struct {
	L int64
	C uint32
}

// Less is the total order on hybrid timestamps.
func (a HLCTime) Less(b HLCTime) bool { return a.L < b.L || (a.L == b.L && a.C < b.C) }

// HLC is a hybrid logical clock: it follows the physical clock when that moves forward and
// uses the counter otherwise, so it never goes backwards and respects causality across machines.
type HLC struct {
	mu    sync.Mutex
	clock Clock
	last  HLCTime
}

func NewHLC(c Clock) *HLC { return &HLC{clock: c} }

// Now stamps a local or send event.
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

// Receive stamps the receipt of a message that carried m.
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

// Seq is the clock for a single writer: a counter that only goes up.
type Seq struct {
	mu sync.Mutex
	n  uint64
}

func (s *Seq) Next() uint64 {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.n++
	return s.n
}
