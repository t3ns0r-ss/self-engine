package clk

import (
	"sync"
	"testing"
)

func TestLamportRules(t *testing.T) {
	var l Lamport
	if a, b := l.Tick(), l.Tick(); a != 1 || b != 2 {
		t.Fatalf("two ticks gave %d and %d, want 1 and 2", a, b)
	}
	if got := l.Receive(10); got != 11 {
		t.Fatalf("receive of 10 at time 2 gave %d, want 11", got)
	}
	if got := l.Receive(5); got != 12 {
		t.Fatalf("receive of 5 at time 11 gave %d, want 12 (the clock never goes back)", got)
	}
	if got := l.Send(); got != 13 || l.Time() != 13 {
		t.Fatalf("send gave %d, Time %d, want 13", got, l.Time())
	}
}

func TestReceiveIsAfterSend(t *testing.T) {
	a, b := NewProcess("A"), NewProcess("B")
	for i := 0; i < 5; i++ {
		b.Local("busy") // B's clock runs ahead of A's
	}
	m := a.Send("hello")
	got := b.Receive(m)
	if got.L <= m.L {
		t.Fatalf("receive stamp %d is not after send stamp %d", got.L, m.L)
	}
	m2 := b.Send("reply")
	if got := a.Receive(m2); got.L <= m2.L {
		t.Fatalf("A is behind B: receive stamp %d must exceed %d", got.L, m2.L)
	}
}

func TestChainOfMessagesIncreases(t *testing.T) {
	a, b, c := NewProcess("A"), NewProcess("B"), NewProcess("C")
	m1 := a.Send("1")
	b.Receive(m1)
	m2 := b.Send("2")
	c.Receive(m2)
	m3 := c.Send("3")
	last := a.Receive(m3)
	prev := uint64(0)
	for _, s := range []uint64{m1.L, b.Log()[0].L, m2.L, c.Log()[0].L, m3.L, last.L} {
		if s <= prev {
			t.Fatalf("chain A to B to C to A is not increasing: %d after %d", s, prev)
		}
		prev = s
	}
}

func TestReorderedDeliveryKeepsEachProcessIncreasing(t *testing.T) {
	a, b := NewProcess("A"), NewProcess("B")
	m1, m2, m3 := a.Send("1"), a.Send("2"), a.Send("3")
	b.Receive(m3) // delivered in the order 3, 1, 2
	b.Receive(m1)
	b.Receive(m2)
	log := b.Log()
	if len(log) != 3 || log[0].Label != "recv 3" || log[1].Label != "recv 1" || log[2].Label != "recv 2" {
		t.Fatalf("log %v", log)
	}
	for i := 1; i < len(log); i++ {
		if log[i].L <= log[i-1].L {
			t.Fatalf("B's stamps %v are not increasing", log)
		}
	}
	if log[0].L <= m3.L {
		t.Fatalf("receive of 3 (%d) must be after its send (%d)", log[0].L, m3.L)
	}
}

func TestLogHasLabelsAndOwner(t *testing.T) {
	a := NewProcess("A")
	a.Local("work")
	m := a.Send("x")
	log := a.Log()
	if len(log) != 2 || log[0].Proc != "A" || log[0].Label != "work" || log[0].L != 1 || log[1].Label != "send x" || log[1].L != 2 || m.From != "A" || m.Payload != "x" || m.L != 2 {
		t.Fatalf("log %v message %v", log, m)
	}
	log[0].L = 99 // changing the returned copy must not change the process
	if a.Log()[0].L != 1 {
		t.Fatal("Log returned the internal slice")
	}
}

func TestConcurrentUse(t *testing.T) {
	p := NewProcess("A")
	var wg sync.WaitGroup
	for g := 0; g < 20; g++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for i := 0; i < 50; i++ {
				p.Local("w")
				p.Receive(Msg{From: "B", Payload: "m", L: uint64(i)})
			}
		}()
	}
	wg.Wait()
	log := p.Log()
	if len(log) != 2000 {
		t.Fatalf("%d events, want 2000", len(log))
	}
	for i := 1; i < len(log); i++ {
		if log[i].L <= log[i-1].L {
			t.Fatalf("event %d: %d after %d", i, log[i].L, log[i-1].L)
		}
	}
}
