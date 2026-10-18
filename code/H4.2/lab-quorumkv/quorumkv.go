// Package quorumkv is the H4.2 lab: a key-value store replicated on N nodes with
// write quorum W and read quorum R, running on simnet in tests and over HTTP in cmd/.
package quorumkv

import (
	"errors"
	"fmt"
	"sort"
	"sync"
)

// Caller sends one request to a node and returns its reply. simnet.Net implements it in tests;
// cmd/client implements it over HTTP for the real multi-process version.
type Caller interface {
	Call(from, to string, req any) (any, error)
}

// Registrar lets a replica receive requests. simnet.Net implements it; cmd/node uses an HTTP server.
type Registrar interface {
	Register(id string, h func(from string, req any) any)
}

// Versioned is a value with its per-key version. The lab assumes the caller supplies
// versions that grow for each key (the claim's stated assumption).
type Versioned struct {
	Value   string
	Version uint64
}

// PutReq asks a replica to store a version of a key; GetReq asks for what it holds.
type PutReq struct {
	Key string
	V   Versioned
}
type GetReq struct{ Key string }

// Replica stores the newest version it has seen of each key.
type Replica struct {
	mu   sync.Mutex
	data map[string]Versioned
}

func NewReplica(net Registrar, id string) *Replica {
	r := &Replica{data: map[string]Versioned{}}
	net.Register(id, r.Handle)
	return r
}

// Handle answers one request; cmd/node calls it from its HTTP handler.
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

var ErrNoQuorum = errors.New("quorumkv: not enough replicas answered")

// Client talks to all N replicas in parallel and waits for W (writes) or R (reads) answers.
// ReadRepair writes the newest version back to every replica that answered with an older one.
// Spares are stand-in nodes used when a home replica is unreachable (a sloppy quorum).
type Client struct {
	Net        Caller
	ID         string
	Replicas   []string
	Spares     []string
	W, R       int
	ReadRepair bool
}

type reply struct {
	from string
	resp any
}

// fanOut calls every node in ids concurrently and returns the successful replies.
func (c *Client) fanOut(ids []string, req any) []reply {
	var mu sync.Mutex
	var wg sync.WaitGroup
	var replies []reply
	for _, id := range ids {
		wg.Add(1)
		go func(id string) {
			defer wg.Done()
			if resp, err := c.Net.Call(c.ID, id, req); err == nil {
				mu.Lock()
				replies = append(replies, reply{id, resp})
				mu.Unlock()
			}
		}(id)
	}
	wg.Wait()
	sort.Slice(replies, func(i, j int) bool { return replies[i].from < replies[j].from }) // same order every run
	return replies
}

func (c *Client) Put(key string, v Versioned) error {
	acks := len(c.fanOut(c.Replicas, PutReq{key, v}))
	if acks < c.W && len(c.Spares) > 0 {
		// Sloppy quorum: borrow spares for the replicas that did not answer.
		missing := len(c.Replicas) - acks
		if missing > len(c.Spares) {
			missing = len(c.Spares)
		}
		acks += len(c.fanOut(c.Spares[:missing], PutReq{key, v}))
	}
	if acks < c.W {
		return fmt.Errorf("%w: %d of %d acks", ErrNoQuorum, acks, c.W)
	}
	return nil
}

// Get returns the newest version among the replies, if at least R replicas answered.
func (c *Client) Get(key string) (Versioned, error) {
	replies := c.fanOut(c.Replicas, GetReq{key})
	if len(replies) < c.R {
		return Versioned{}, fmt.Errorf("%w: %d of %d replies", ErrNoQuorum, len(replies), c.R)
	}
	var best Versioned
	for _, r := range replies {
		if v := r.resp.(Versioned); v.Version > best.Version {
			best = v
		}
	}
	if c.ReadRepair && best.Version > 0 {
		for _, r := range replies {
			if r.resp.(Versioned).Version < best.Version {
				c.Net.Call(c.ID, r.from, PutReq{key, best}) // best effort; a failed repair is retried by the next read
			}
		}
	}
	return best, nil
}

// Snapshot returns what one replica holds for a key, bypassing the quorum (for tests and run.md).
func Snapshot(net Caller, id, key string) Versioned {
	resp, err := net.Call("probe", id, GetReq{key})
	if err != nil {
		return Versioned{}
	}
	return resp.(Versioned)
}

// NewStandaloneReplica makes a replica that is not registered on a simulated network (cmd/node serves it over HTTP).
func NewStandaloneReplica() *Replica { return &Replica{data: map[string]Versioned{}} }
