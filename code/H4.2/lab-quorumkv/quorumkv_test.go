package quorumkv

import (
	"errors"
	"fmt"
	"sync"
	"testing"

	"selfengine/code/shared/go/simnet"
)

func setup(w, r int) (*simnet.Net, *Client, *Client) {
	net := simnet.New()
	ids := []string{"A", "B", "C"}
	for _, id := range ids {
		NewReplica(net, id)
	}
	writer := &Client{Net: net, ID: "writer", Replicas: ids, W: w, R: r}
	reader := &Client{Net: net, ID: "reader", Replicas: ids, W: w, R: r}
	return net, writer, reader
}

func TestSurvivesOneReplicaDown(t *testing.T) {
	net, w, r := setup(2, 2)
	net.SetDown("C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	got, err := r.Get("k")
	if err != nil || got.Value != "v1" {
		t.Fatalf("got %v, %v; want v1", got, err)
	}
}

// W + R > N: the write reached {A, B}; the read reaches {B, C}; they share B.
func TestReadMeetsAcknowledgedWrite(t *testing.T) {
	net, w, r := setup(2, 2)
	net.Partition("writer", "C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.Partition("reader", "A", true)
	got, err := r.Get("k")
	if err != nil || got.Value != "v1" {
		t.Fatalf("got %v, %v; want v1", got, err)
	}
}

// W + R = 2, not greater than 3: the write reached only A; the read reaches only C.
func TestW1R1CanReturnStale(t *testing.T) {
	net, w, r := setup(1, 1)
	net.Partition("writer", "B", true)
	net.Partition("writer", "C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.Partition("reader", "A", true)
	net.Partition("reader", "B", true)
	got, err := r.Get("k")
	if err != nil {
		t.Fatal(err)
	}
	if got.Value != "" {
		t.Fatalf("expected a stale (empty) read, got %v", got)
	}
}

func TestNoQuorumWithTwoDown(t *testing.T) {
	net, w, _ := setup(2, 2)
	net.SetDown("B", true)
	net.SetDown("C", true)
	if err := w.Put("k", Versioned{"v1", 1}); !errors.Is(err, ErrNoQuorum) {
		t.Fatalf("got %v, want ErrNoQuorum", err)
	}
}

// A replica that missed a write is stale until a read with repair reaches it.
func TestReadRepairHealsStaleReplica(t *testing.T) {
	net, w, r := setup(2, 3)
	net.SetDown("C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.SetDown("C", false)
	if got := Snapshot(net, "C", "k"); got.Version != 0 {
		t.Fatalf("C should be stale before the read, has %v", got)
	}
	r.ReadRepair = true
	if got, err := r.Get("k"); err != nil || got.Value != "v1" {
		t.Fatalf("got %v, %v; want v1", got, err)
	}
	if got := Snapshot(net, "C", "k"); got.Value != "v1" {
		t.Fatalf("C should be repaired, has %v", got)
	}
}

// Without repair the same read leaves C stale (the contrast for the test above).
func TestWithoutRepairReplicaStaysStale(t *testing.T) {
	net, w, r := setup(2, 3)
	net.SetDown("C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.SetDown("C", false)
	if _, err := r.Get("k"); err != nil {
		t.Fatal(err)
	}
	if got := Snapshot(net, "C", "k"); got.Version != 0 {
		t.Fatalf("C should still be stale, has %v", got)
	}
}

// Sloppy quorum: with C unreachable the write is acknowledged by A and spare D, so W + R > N holds
// by count, but the read set {B, C} has nothing in common with the write set {A, D}.
func TestSloppyQuorumBreaksOverlap(t *testing.T) {
	net, w, r := setup(2, 2)
	NewReplica(net, "D")
	w.Spares = []string{"D"}
	net.SetDown("B", true) // B is down for the write only
	net.Partition("writer", "C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.SetDown("B", false)
	net.Partition("writer", "C", false)
	net.Partition("reader", "A", true) // the read reaches B and C, the two replicas without the write
	got, err := r.Get("k")
	if err != nil {
		t.Fatal(err)
	}
	if got.Value != "" {
		t.Fatalf("expected a stale read through a sloppy quorum, got %v", got)
	}
}

// A and B hold version 1; only C holds version 2. A read of all three must return version 2,
// not the first reply it happens to get.
func TestGetReturnsNewestOfReplies(t *testing.T) {
	net, w, r := setup(1, 3)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.Partition("writer", "A", true)
	net.Partition("writer", "B", true)
	if err := w.Put("k", Versioned{"v2", 2}); err != nil {
		t.Fatal(err)
	}
	got, err := r.Get("k")
	if err != nil || got.Value != "v2" {
		t.Fatalf("got %v, %v; want v2", got, err)
	}
}

// A late, older write must not replace a newer value.
func TestOlderVersionDoesNotOverwrite(t *testing.T) {
	_, w, r := setup(3, 3)
	if err := w.Put("k", Versioned{"v2", 2}); err != nil {
		t.Fatal(err)
	}
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	got, err := r.Get("k")
	if err != nil || got.Value != "v2" {
		t.Fatalf("got %v, %v; want v2", got, err)
	}
}

// Run with -race: many clients writing different keys at once.
func TestConcurrentClients(t *testing.T) {
	net, _, _ := setup(2, 2)
	var wg sync.WaitGroup
	for i := 0; i < 50; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			c := &Client{Net: net, ID: fmt.Sprintf("c%d", i), Replicas: []string{"A", "B", "C"}, W: 2, R: 2}
			key := fmt.Sprintf("k%d", i%5)
			if err := c.Put(key, Versioned{"x", uint64(i + 1)}); err != nil {
				t.Error(err)
			}
			if _, err := c.Get(key); err != nil {
				t.Error(err)
			}
		}(i)
	}
	wg.Wait()
}
