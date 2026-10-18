package kv

import (
	"errors"
	"fmt"
	"sync"
	"testing"
)

var _ = errors.Is
var _ = fmt.Sprint
var _ sync.Mutex

func TestPutThenGet(t *testing.T) {
	_, w, r := newCluster(2, 2)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	got, err := r.Get("k")
	if err != nil || got != (Versioned{"v1", 1}) {
		t.Fatalf("got %v, %v; want v1", got, err)
	}
}

func TestUnknownKeyReadsEmpty(t *testing.T) {
	_, _, r := newCluster(2, 2)
	got, err := r.Get("nothing")
	if err != nil || got != (Versioned{}) {
		t.Fatalf("got %v, %v; want the zero Versioned", got, err)
	}
}

func TestGetReturnsNewestOfReplies(t *testing.T) {
	net, _, r := newCluster(2, 2)
	net.Call("x", "C", PutReq{"k", Versioned{"v2", 2}}) // only C holds version 2
	net.Call("x", "A", PutReq{"k", Versioned{"v1", 1}})
	net.Call("x", "B", PutReq{"k", Versioned{"v1", 1}})
	got, err := r.Get("k")
	if err != nil || got.Value != "v2" {
		t.Fatalf("got %v, %v; want v2 from the one replica that has it", got, err)
	}
}

func TestOlderVersionDoesNotOverwrite(t *testing.T) {
	_, w, r := newCluster(2, 2)
	w.Put("k", Versioned{"v2", 2})
	w.Put("k", Versioned{"v1", 1})
	got, err := r.Get("k")
	if err != nil || got.Value != "v2" {
		t.Fatalf("got %v, %v; want v2", got, err)
	}
}

func TestConcurrentClients(t *testing.T) {
	net, _, _ := newCluster(2, 2)
	var wg sync.WaitGroup
	for i := 0; i < 40; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			c := &Client{Net: net, ID: fmt.Sprintf("c%d", i), Replicas: ids, W: 2, R: 2}
			if err := c.Put("shared", Versioned{fmt.Sprint("v", i+1), uint64(i + 1)}); err != nil {
				t.Error(err)
			}
		}()
	}
	wg.Wait()
	_, _, r := newCluster(2, 2)
	r.Net = net
	got, err := r.Get("shared")
	if err != nil || got.Version != 40 {
		t.Fatalf("got %v, %v; want version 40", got, err)
	}
}

func TestOneReplicaDownStillWorks(t *testing.T) {
	net, w, r := newCluster(2, 2)
	net.SetDown("C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatalf("put with one replica down: %v", err)
	}
	got, err := r.Get("k")
	if err != nil || got.Value != "v1" {
		t.Fatalf("get with one replica down: %v, %v", got, err)
	}
}

func TestCutLinkStillWorks(t *testing.T) {
	net, w, r := newCluster(2, 2)
	net.Cut("writer", "A", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.Cut("reader", "C", true)
	got, err := r.Get("k")
	if err != nil || got.Value != "v1" {
		t.Fatalf("got %v, %v; want v1 (the write reached B and C, the read reaches A and B)", got, err)
	}
}

func TestTwoDownMeansNoQuorum(t *testing.T) {
	net, w, r := newCluster(2, 2)
	net.SetDown("B", true)
	net.SetDown("C", true)
	if err := w.Put("k", Versioned{"v1", 1}); !errors.Is(err, ErrNoQuorum) {
		t.Fatalf("put: got %v, want ErrNoQuorum", err)
	}
	if _, err := r.Get("k"); !errors.Is(err, ErrNoQuorum) {
		t.Fatalf("get: got %v, want ErrNoQuorum", err)
	}
}

func TestNewClientRefusesUnsafeSettings(t *testing.T) {
	net, _, _ := newCluster(2, 2)
	if _, err := NewClient(net, "c", ids, 1, 1, false); !errors.Is(err, ErrUnsafeQuorum) {
		t.Fatalf("W=1,R=1: got %v, want ErrUnsafeQuorum", err)
	}
	if _, err := NewClient(net, "c", ids, 2, 1, false); !errors.Is(err, ErrUnsafeQuorum) {
		t.Fatalf("W=2,R=1 (W+R = N): got %v, want ErrUnsafeQuorum", err)
	}
}

func TestNewClientAcceptsOverlappingSettings(t *testing.T) {
	net, _, _ := newCluster(2, 2)
	for _, wr := range [][2]int{{2, 2}, {3, 1}, {1, 3}, {3, 3}} {
		if _, err := NewClient(net, "c", ids, wr[0], wr[1], false); err != nil {
			t.Fatalf("W=%d,R=%d: %v", wr[0], wr[1], err)
		}
	}
}

func TestNewClientRejectsOutOfRange(t *testing.T) {
	net, _, _ := newCluster(2, 2)
	for _, wr := range [][2]int{{0, 3}, {3, 0}, {4, 1}, {1, 4}} {
		if _, err := NewClient(net, "c", ids, wr[0], wr[1], true); err == nil {
			t.Fatalf("W=%d,R=%d accepted; want an error", wr[0], wr[1])
		}
	}
}

func TestAllowStaleReallyCanReadStale(t *testing.T) {
	net, _, _ := newCluster(2, 2)
	w, _ := NewClient(net, "writer", ids, 1, 1, true)
	r, err := NewClient(net, "reader", ids, 1, 1, true)
	if err != nil {
		t.Fatal(err)
	}
	net.Cut("writer", "B", true)
	net.Cut("writer", "C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.Cut("reader", "A", true)
	net.Cut("reader", "B", true)
	got, err := r.Get("k")
	if err != nil || got.Version != 0 {
		t.Fatalf("got %v, %v; want a stale (empty) read", got, err)
	}
}
