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
// PutReq stores the version only if it is newer than what the replica holds and returns true;
// GetReq returns the stored Versioned (the zero value if the key is unknown).
func (r *Replica) Handle(_ string, req any) any { panic("not implemented") }

// Client talks to all replicas in parallel.
type Client struct {
	Net      Caller
	ID       string
	Replicas []string
	W, R     int
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

// Put stores v on every replica. In this rung every replica must answer; any failed call is an error.
func (c *Client) Put(key string, v Versioned) error { panic("not implemented") }

// Get returns the newest version among the replies. In this rung every replica must answer.
func (c *Client) Get(key string) (Versioned, error) { panic("not implemented") }
