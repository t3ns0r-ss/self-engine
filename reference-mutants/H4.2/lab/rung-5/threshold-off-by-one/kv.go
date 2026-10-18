// Package kv is a quorum key-value store: N replicas, write quorum W, read quorum R.
package kv

import (
	"errors"
	"fmt"
	"sync"
)

// Caller sends one request to a node and returns its reply (the tests supply a fake network).
type Caller interface {
	Call(from, to string, req any) (any, error)
}

// Versioned is a value with its per-key version. Callers supply versions that grow for each key.
type Versioned struct {
	Value   string
	Version uint64
}

// PutReq asks a replica to store a version of a key; GetReq asks for what it holds (the zero Versioned if nothing).
type PutReq struct {
	Key string
	V   Versioned
}
type GetReq struct{ Key string }

// ErrNoQuorum is returned (wrapped) when fewer than W (writes) or R (reads) replicas answered.
var ErrNoQuorum = errors.New("kv: not enough replicas answered")

// Replica stores the newest version it has seen of each key.
type Replica struct {
	mu   sync.Mutex
	data map[string]Versioned
}

func NewReplica() *Replica { return &Replica{data: map[string]Versioned{}} }

// Handle answers one request. It may be called from many goroutines at once.
func (r *Replica) Handle(_ string, req any) any {
	r.mu.Lock()
	defer r.mu.Unlock()
	switch m := req.(type) {
	case PutReq:
		if m.V.Version > r.data[m.Key].Version { // keep only newer versions
			r.data[m.Key] = m.V
		}
		return true
	case GetReq:
		return r.data[m.Key]
	}
	return nil
}

// Client talks to all replicas in parallel.
type Client struct {
	Net      Caller
	ID       string
	Replicas []string
	W, R     int
	ReadRepair bool // rung 4: write the newest version back to stale replicas after a read
}

// call sends req to every replica at once. results[i] is nil when replica i did not answer.
func (c *Client) call(req any) []any {
	results := make([]any, len(c.Replicas))
	var wg sync.WaitGroup
	for i, id := range c.Replicas {
		wg.Add(1)
		go func() {
			defer wg.Done()
			if resp, err := c.Net.Call(c.ID, id, req); err == nil {
				results[i] = resp
			}
		}()
	}
	wg.Wait()
	return results
}

func answered(results []any) int {
	n := 0
	for _, r := range results {
		if r != nil {
			n++
		}
	}
	return n
}

// newest returns the highest-version reply among the non-nil results.
func newest(results []any) Versioned {
	var best Versioned
	for _, r := range results {
		if r != nil && r.(Versioned).Version > best.Version {
			best = r.(Versioned)
		}
	}
	return best
}

// Put stores v on every replica and succeeds when at least W acknowledged.
func (c *Client) Put(key string, v Versioned) error {
	acks := answered(c.call(PutReq{key, v}))
	if acks < c.W {
		return fmt.Errorf("%w: %d of %d acks", ErrNoQuorum, acks, c.W)
	}
	return nil
}

// Get asks every replica and returns the newest version, if at least R answered.
// With ReadRepair set it then writes the newest version back to each replica that answered with an older one;
// a failed repair never fails the read.
func (c *Client) Get(key string) (Versioned, error) {
	results := c.call(GetReq{key})
	if n := answered(results); n < c.R {
		return Versioned{}, fmt.Errorf("%w: %d of %d replies", ErrNoQuorum, n, c.R)
	}
	best := newest(results)
	if c.ReadRepair && best.Version > 0 {
		for i, r := range results {
			if r != nil && r.(Versioned).Version < best.Version {
				c.Net.Call(c.ID, c.Replicas[i], PutReq{key, best})
			}
		}
	}
	return best, nil
}

// ErrUnsafeQuorum is returned by NewClient when W + R <= N and the caller did not opt in to stale reads.
var ErrUnsafeQuorum = errors.New("kv: W + R must be greater than N")

// NewClient checks the setting. W and R must each be between 1 and N. When W + R <= N a read can miss an
// acknowledged write, so NewClient refuses with ErrUnsafeQuorum unless allowStale is true.
func NewClient(net Caller, id string, replicas []string, w, r int, allowStale bool) (*Client, error) {
	n := len(replicas)
	if w < 1 || r < 1 || w > n || r > n {
		return nil, fmt.Errorf("kv: W and R must be between 1 and %d", n)
	}
	if w+r <= n && !allowStale {
		return nil, ErrUnsafeQuorum
	}
	return &Client{Net: net, ID: id, Replicas: replicas, W: w, R: r}, nil
}
