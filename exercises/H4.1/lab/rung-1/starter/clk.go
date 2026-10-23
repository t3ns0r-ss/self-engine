// Package clk is a small logical-clock library: Lamport clocks and processes that stamp their events.
package clk

// Lamport is a logical clock. A local or send event adds 1; a receive sets the counter to
// max(own, received) + 1. It must be safe for use from many goroutines.
type Lamport struct {
	// add your fields
}

// Tick records a local event and returns its timestamp.
func (l *Lamport) Tick() uint64 { panic("not implemented") }

// Send records a send event and returns the timestamp that travels with the message.
func (l *Lamport) Send() uint64 { panic("not implemented") }

// Receive records the receipt of a message stamped remote and returns the new timestamp.
func (l *Lamport) Receive(remote uint64) uint64 { panic("not implemented") }

// Time returns the current counter without recording an event.
func (l *Lamport) Time() uint64 { panic("not implemented") }

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
	ID string
	// add your fields
}

func NewProcess(id string) *Process { panic("not implemented") }

// Local records an event with no message.
func (p *Process) Local(label string) Stamp { panic("not implemented") }

// Send records a send event (label "send " + payload) and returns the message to deliver.
func (p *Process) Send(payload string) Msg { panic("not implemented") }

// Receive records the receipt of m (label "recv " + payload).
func (p *Process) Receive(m Msg) Stamp { panic("not implemented") }

// Log returns this process's events in the order they happened here.
func (p *Process) Log() []Stamp { panic("not implemented") }
