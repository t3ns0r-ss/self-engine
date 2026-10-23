// Package clk is a small logical-clock library: Lamport clocks and processes that stamp their events.
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

// Msg is a message in transit: the payload and the sender's Lamport time at the send event.
type Msg struct {
	From    string
	Payload string
	L       uint64
}

// Stamp is one recorded event.
type Stamp struct {
	Proc, Label string
	L           uint64
}

// Process stamps its events. There is no network here: Send returns the message and the caller
// delivers it (in any order, or never) by calling Receive on the destination.
type Process struct {
	ID  string
	mu  sync.Mutex
	lam Lamport
	log []Stamp
}

func NewProcess(id string) *Process { return &Process{ID: id} }

// Local records an event with no message.
func (p *Process) Local(label string) Stamp {
	p.mu.Lock()
	defer p.mu.Unlock()
	return p.record(label, p.lam.Tick())
}

// Send records a send event and returns the message to deliver.
func (p *Process) Send(payload string) Msg {
	p.mu.Lock()
	defer p.mu.Unlock()
	l := p.lam.Send()
	p.record("send "+payload, l)
	return Msg{From: p.ID, Payload: payload, L: l}
}

// Receive records the receipt of m.
func (p *Process) Receive(m Msg) Stamp {
	p.mu.Lock()
	defer p.mu.Unlock()
	return p.record("recv "+m.Payload, p.lam.Receive(m.L))
}

// Log returns this process's events in the order they happened here.
func (p *Process) Log() []Stamp {
	p.mu.Lock()
	defer p.mu.Unlock()
	return append([]Stamp(nil), p.log...)
}

// record stores the stamp; the caller holds p.mu.
func (p *Process) record(label string, l uint64) Stamp {
	s := Stamp{Proc: p.ID, Label: label, L: l}
	p.log = append(p.log, s)
	return s
}
