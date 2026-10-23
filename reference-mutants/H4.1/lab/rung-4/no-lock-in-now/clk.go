// Package clk is a small logical-clock library: Lamport clocks, vector clocks, and processes that
// stamp their events with both.
package clk

import "sync"

// Lamport is a logical clock. A local or send event adds 1; a receive sets the counter to
// max(own, received) + 1. It is safe for use from many goroutines.
type Lamport struct {
	mu sync.Mutex
	t  uint64
}

// Tick records a local event and returns its timestamp.
func (l *Lamport) Tick() uint64 {
	l.mu.Lock()
	defer l.mu.Unlock()
	l.t++
	return l.t
}

// Send records a send event and returns the timestamp that travels with the message.
func (l *Lamport) Send() uint64 { return l.Tick() }

// Receive records the receipt of a message stamped remote and returns the new timestamp.
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
// None of the methods changes the clock it is called on, so a VC sent in a message can be shared.
type VC map[string]uint64

// Order is the relation between two vector clocks.
type Order int

const (
	Equal      Order = iota // the same events seen
	Before                  // a happened before b
	After                   // b happened before a
	Concurrent              // neither saw the other
)

// Copy returns an independent copy.
func (v VC) Copy() VC {
	out := make(VC, len(v))
	for k, n := range v {
		out[k] = n
	}
	return out
}

// Inc returns a copy of v with id's entry increased by one.
func (v VC) Inc(id string) VC {
	out := v.Copy()
	out[id]++
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

// Compare says how a and b are ordered: Before when every entry of a is at most the matching entry
// of b and one is smaller; Concurrent when each has an entry larger than the other's.
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

// Msg is a message in transit: the payload and the sender's stamps at the send event.
type Msg struct {
	From    string
	Payload string
	L       uint64
	V       VC
}

// Stamp is one recorded event.
type Stamp struct {
	Proc, Label string
	L           uint64
	V           VC
}

// Process stamps its events with a Lamport time and a vector clock. There is no network here:
// Send returns the message and the caller delivers it by calling Receive on the destination.
type Process struct {
	ID  string
	mu  sync.Mutex
	lam Lamport
	vc  VC
	log []Stamp
}

func NewProcess(id string) *Process { return &Process{ID: id, vc: VC{}} }

// Local records an event with no message.
func (p *Process) Local(label string) Stamp {
	p.mu.Lock()
	defer p.mu.Unlock()
	return p.record(label, p.lam.Tick(), p.vc.Inc(p.ID))
}

// Send records a send event and returns the message to deliver.
func (p *Process) Send(payload string) Msg {
	p.mu.Lock()
	defer p.mu.Unlock()
	l, v := p.lam.Send(), p.vc.Inc(p.ID)
	p.record("send "+payload, l, v)
	return Msg{From: p.ID, Payload: payload, L: l, V: v.Copy()}
}

// Receive records the receipt of m.
func (p *Process) Receive(m Msg) Stamp {
	p.mu.Lock()
	defer p.mu.Unlock()
	return p.record("recv "+m.Payload, p.lam.Receive(m.L), Merge(p.vc, m.V).Inc(p.ID))
}

// Log returns this process's events in the order they happened here.
func (p *Process) Log() []Stamp {
	p.mu.Lock()
	defer p.mu.Unlock()
	out := make([]Stamp, len(p.log))
	for i, s := range p.log {
		out[i] = Stamp{s.Proc, s.Label, s.L, s.V.Copy()}
	}
	return out
}

// record stores the stamp; the caller holds p.mu.
func (p *Process) record(label string, l uint64, v VC) Stamp {
	p.vc = v
	p.log = append(p.log, Stamp{p.ID, label, l, v.Copy()})
	return Stamp{p.ID, label, l, v.Copy()} // the caller gets its own copy
}
