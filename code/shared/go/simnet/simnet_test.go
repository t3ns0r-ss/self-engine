package simnet

import (
	"errors"
	"testing"
)

func TestDownAndPartition(t *testing.T) {
	n := New()
	n.Register("A", func(from string, req any) any { return req })
	if r, err := n.Call("c", "A", 7); err != nil || r != 7 {
		t.Fatalf("got %v, %v; want 7", r, err)
	}
	n.SetDown("A", true)
	if _, err := n.Call("c", "A", 1); !errors.Is(err, ErrUnreachable) {
		t.Fatalf("down node: got %v, want ErrUnreachable", err)
	}
	n.SetDown("A", false)
	n.Partition("c", "A", true)
	if _, err := n.Call("c", "A", 1); !errors.Is(err, ErrUnreachable) {
		t.Fatalf("cut link: got %v, want ErrUnreachable", err)
	}
	n.Partition("c", "A", false)
	if _, err := n.Call("c", "A", 1); err != nil {
		t.Fatalf("healed link: got %v", err)
	}
}
