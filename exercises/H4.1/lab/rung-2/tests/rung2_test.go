package clk

import (
	"reflect"
	"sync"
	"testing"
)

func TestCompareCases(t *testing.T) {
	cases := []struct {
		a, b VC
		want Order
	}{
		{VC{}, VC{}, Equal},
		{VC{"A": 1}, VC{"A": 1}, Equal},
		{VC{"A": 1}, VC{"A": 2}, Before},
		{VC{"A": 2, "B": 1}, VC{"A": 1}, After},
		{VC{"A": 1}, VC{"B": 1}, Concurrent},
		{VC{"A": 2, "B": 1}, VC{"A": 1, "B": 2}, Concurrent},
		{VC{"A": 1}, VC{"A": 1, "B": 1}, Before},
		{VC{"A": 0}, VC{}, Equal},
		{VC{"A": 3}, VC{"B": 1}, Concurrent},
		{VC{"A": 1, "B": 5}, VC{"A": 2}, Concurrent},
	}
	for _, c := range cases {
		if got := Compare(c.a, c.b); got != c.want {
			t.Errorf("Compare(%v, %v) = %v, want %v", c.a, c.b, got, c.want)
		}
	}
}

func TestMergeAndIncDoNotChangeTheirInputs(t *testing.T) {
	a, b := VC{"A": 2}, VC{"A": 1, "B": 3}
	m := Merge(a, b)
	if !reflect.DeepEqual(m, VC{"A": 2, "B": 3}) {
		t.Fatalf("merge gave %v", m)
	}
	i := a.Inc("A")
	if i["A"] != 3 || a["A"] != 2 || !reflect.DeepEqual(b, VC{"A": 1, "B": 3}) {
		t.Fatalf("inc gave %v; inputs are now %v and %v", i, a, b)
	}
}

func TestTwoWritesWithoutMessagesAreConcurrent(t *testing.T) {
	a, b := NewProcess("A"), NewProcess("B")
	w1, w2 := a.Local("x=1"), b.Local("x=2")
	if got := Compare(w1.V, w2.V); got != Concurrent {
		t.Fatalf("got %v, want concurrent", got)
	}
	if w1.L != 1 || w2.L != 1 {
		t.Fatalf("Lamport times are %d and %d; they are still kept", w1.L, w2.L)
	}
}

func TestMessageOrdersTheWrites(t *testing.T) {
	a, b := NewProcess("A"), NewProcess("B")
	w1 := a.Local("x=1")
	m := a.Send("state")
	b.Local("x=2") // before B hears from A: concurrent with w1
	r := b.Receive(m)
	w3 := b.Local("x=3")
	if got := Compare(w1.V, r.V); got != Before {
		t.Fatalf("w1 and the receive: got %v, want before", got)
	}
	if got := Compare(w1.V, w3.V); got != Before {
		t.Fatalf("w1 and w3: got %v, want before", got)
	}
	if got := Compare(w3.V, w1.V); got != After {
		t.Fatalf("w3 and w1: got %v, want after", got)
	}
	if !reflect.DeepEqual(w3.V, VC{"A": 2, "B": 3}) {
		t.Fatalf("w3 has %v, want A:2 B:3", w3.V)
	}
}

func TestEachProcessOnlyMovesForward(t *testing.T) {
	a, b := NewProcess("A"), NewProcess("B")
	for i := 0; i < 5; i++ {
		b.Local("w")
	}
	a.Receive(b.Send("m1"))
	b.Receive(a.Send("m2"))
	b.Receive(Msg{From: "A", Payload: "old", L: 1, V: VC{"A": 1}}) // a late, old message
	for _, p := range []*Process{a, b} {
		log := p.Log()
		for i := 1; i < len(log); i++ {
			if Compare(log[i-1].V, log[i].V) != Before {
				t.Fatalf("%s: event %d has %v after %v", p.ID, i, log[i].V, log[i-1].V)
			}
		}
	}
}

func TestStampsDoNotShareMemory(t *testing.T) {
	a, b := NewProcess("A"), NewProcess("B")
	m := a.Send("x")
	b.Receive(m)
	m.V["A"] = 100 // the receiver must have copied what it needed
	m.V["Z"] = 7
	next := b.Local("y")
	if next.V["A"] != 1 || next.V["Z"] != 0 {
		t.Fatalf("B's clock changed when the sender's map was edited: %v", next.V)
	}
	s := a.Local("z")
	s.V["A"] = 50
	if got := a.Log()[1].V["A"]; got != 2 {
		t.Fatalf("editing a returned stamp changed the process: %d", got)
	}
}

func TestConcurrentUseOfVectorClocks(t *testing.T) {
	p := NewProcess("A")
	var wg sync.WaitGroup
	for g := 0; g < 20; g++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for i := 0; i < 50; i++ {
				p.Local("w")
				p.Receive(Msg{From: "B", Payload: "m", L: 1, V: VC{"B": uint64(i + 1)}})
			}
		}()
	}
	wg.Wait()
	log := p.Log()
	if len(log) != 2000 || log[len(log)-1].V["A"] != 2000 {
		t.Fatalf("%d events, last clock %v", len(log), log[len(log)-1].V)
	}
}
