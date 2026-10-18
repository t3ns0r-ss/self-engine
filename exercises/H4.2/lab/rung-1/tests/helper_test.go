package kv

import (
	"errors"
	"fmt"
	"sync"
	"testing"
)

var _ = errors.Is
var _ *testing.T
var _ = fmt.Sprint

// fakeNet is an in-memory network: nodes can be down, and links can be cut.
type fakeNet struct {
	mu   sync.Mutex
	h    map[string]func(string, any) any
	down map[string]bool
	cut  map[[2]string]bool
}

func newFakeNet() *fakeNet {
	return &fakeNet{h: map[string]func(string, any) any{}, down: map[string]bool{}, cut: map[[2]string]bool{}}
}
func (n *fakeNet) Call(from, to string, req any) (any, error) {
	n.mu.Lock()
	h, ok := n.h[to]
	blocked := !ok || n.down[to] || n.down[from] || n.cut[[2]string{from, to}]
	n.mu.Unlock()
	if blocked {
		return nil, errors.New("unreachable")
	}
	return h(from, req), nil
}
func (n *fakeNet) SetDown(id string, d bool) { n.mu.Lock(); n.down[id] = d; n.mu.Unlock() }
func (n *fakeNet) Cut(a, b string, c bool) {
	n.mu.Lock()
	n.cut[[2]string{a, b}] = c
	n.cut[[2]string{b, a}] = c
	n.mu.Unlock()
}

var ids = []string{"A", "B", "C"}

func newCluster(w, r int) (*fakeNet, *Client, *Client) {
	net := newFakeNet()
	for _, id := range ids {
		net.h[id] = NewReplica().Handle
	}
	return net, &Client{Net: net, ID: "writer", Replicas: ids, W: w, R: r}, &Client{Net: net, ID: "reader", Replicas: ids, W: w, R: r}
}

// held returns what one replica holds for a key, bypassing the client.
func held(net *fakeNet, id, key string) Versioned {
	resp, err := net.Call("probe", id, GetReq{key})
	if err != nil {
		return Versioned{}
	}
	return resp.(Versioned)
}
