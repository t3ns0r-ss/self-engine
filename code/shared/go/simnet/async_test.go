package simnet

import (
	"fmt"
	"reflect"
	"testing"
	"time"
)

// runOnce sends 20 numbered messages with random delays and returns the delivery order.
func runOnce(seed int64) []string {
	n := NewAsync(seed)
	n.SetDelay(1*time.Millisecond, 50*time.Millisecond)
	var got []string
	n.Register("B", func(from string, msg any) { got = append(got, fmt.Sprint(msg)) })
	for i := 0; i < 20; i++ {
		n.Send("A", "B", i)
	}
	n.RunUntilIdle(1000)
	return got
}

func TestSameSeedSameOrderDifferentSeedDifferentOrder(t *testing.T) {
	a, b := runOnce(1), runOnce(1)
	if !reflect.DeepEqual(a, b) {
		t.Fatalf("same seed gave different orders:\n%v\n%v", a, b)
	}
	if len(a) != 20 {
		t.Fatalf("delivered %d messages, want 20", len(a))
	}
	if reflect.DeepEqual(a, runOnce(2)) {
		t.Fatalf("different seeds gave the same order: %v", a)
	}
	inOrder := true
	for i, s := range a {
		if s != fmt.Sprint(i) {
			inOrder = false
		}
	}
	if inOrder {
		t.Fatal("expected at least one reordered message with delays 1-50 ms")
	}
}

func TestClockAdvancesOnlyWhenStepping(t *testing.T) {
	n := NewAsync(1)
	n.SetDelay(10*time.Millisecond, 10*time.Millisecond)
	delivered := 0
	n.Register("B", func(string, any) { delivered++ })
	start := n.Now()
	n.Send("A", "B", 1)
	if !n.Now().Equal(start) || delivered != 0 {
		t.Fatal("sending must not move the clock or deliver")
	}
	n.Step()
	if got := n.Now().Sub(start); got != 10*time.Millisecond || delivered != 1 {
		t.Fatalf("after Step: clock +%v, delivered %d; want +10ms, 1", got, delivered)
	}
	if n.Step() {
		t.Fatal("Step on an empty queue must report false")
	}
}

func TestTimersAndFailuresOnVirtualClock(t *testing.T) {
	n := NewAsync(7)
	var fired []time.Duration
	base := n.Now()
	n.AfterFunc(300*time.Millisecond, func() { fired = append(fired, n.Now().Sub(base)) })
	n.AfterFunc(100*time.Millisecond, func() { fired = append(fired, n.Now().Sub(base)) })
	n.RunFor(200 * time.Millisecond)
	if len(fired) != 1 || fired[0] != 100*time.Millisecond {
		t.Fatalf("after 200ms: fired %v, want [100ms]", fired)
	}
	n.RunUntilIdle(10)
	if len(fired) != 2 || fired[1] != 300*time.Millisecond {
		t.Fatalf("fired %v, want [100ms 300ms]", fired)
	}

	got := 0
	n.Register("B", func(string, any) { got++ })
	n.SetDown("B", true)
	n.Send("A", "B", 1)
	n.RunUntilIdle(10)
	n.SetDown("B", false)
	n.Partition("A", "B", true)
	n.Send("A", "B", 2)
	n.RunUntilIdle(10)
	n.Partition("A", "B", false)
	n.Send("A", "B", 3)
	n.RunUntilIdle(10)
	if got != 1 {
		t.Fatalf("delivered %d messages, want only the last one", got)
	}
}
