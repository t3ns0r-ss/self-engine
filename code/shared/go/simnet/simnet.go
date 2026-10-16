// Package simnet is a deterministic in-memory network for HLD labs.
// Nodes register a handler; Call delivers a request to a node and returns its reply,
// unless the destination is down or the two nodes are partitioned from each other.
// Tests control failures explicitly, so every run behaves the same way.
package simnet

import (
	"errors"
	"sync"
)

// ErrUnreachable is returned when the destination is down or partitioned from the caller.
var ErrUnreachable = errors.New("simnet: unreachable")

// Handler answers one request. It may be called from many goroutines at once.
type Handler func(from string, req any) any

type Net struct {
	mu       sync.Mutex
	handlers map[string]Handler
	down     map[string]bool
	cut      map[[2]string]bool // cut[{a,b}] means a and b cannot talk (stored both ways)
}

func New() *Net {
	return &Net{handlers: map[string]Handler{}, down: map[string]bool{}, cut: map[[2]string]bool{}}
}

// Register installs the handler for node id. It accepts a plain func so that packages using
// simnet do not need to import the Handler type.
func (n *Net) Register(id string, h func(from string, req any) any) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.handlers[id] = h
}

func (n *Net) SetDown(id string, down bool) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.down[id] = down
}

// Partition cuts (or, with cut=false, heals) the link between a and b in both directions.
func (n *Net) Partition(a, b string, cut bool) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.cut[[2]string{a, b}] = cut
	n.cut[[2]string{b, a}] = cut
}

// Call sends req from one node (or client) to another and returns the reply.
func (n *Net) Call(from, to string, req any) (any, error) {
	n.mu.Lock()
	h, ok := n.handlers[to]
	blocked := !ok || n.down[to] || n.down[from] || n.cut[[2]string{from, to}]
	n.mu.Unlock() // never hold the lock while the handler runs
	if blocked {
		return nil, ErrUnreachable
	}
	return h(from, req), nil
}
