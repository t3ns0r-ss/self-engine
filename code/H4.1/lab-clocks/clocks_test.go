package clocks

import (
	"fmt"
	"math/rand"
	"net/http/httptest"
	"reflect"
	"sort"
	"strings"
	"sync"
	"testing"
	"time"

	"selfengine/code/shared/go/simnet"
)

var ids = []string{"A", "B", "C"}

func trio(seed int64) (*simnet.AsyncNet, map[string]*Process) {
	net := simnet.NewAsync(seed)
	net.SetDelay(1*time.Millisecond, 30*time.Millisecond)
	ps := map[string]*Process{}
	for _, id := range ids {
		ps[id] = NewProcess(id, net)
		net.Register(id, ps[id].Handle)
	}
	return net, ps
}

// randomRun makes 40 random steps (a local event, or a message to another process), letting some
// virtual time pass between steps so that messages overtake each other, and returns every stamp.
func randomRun(seed int64) []Stamp {
	ps := randomProcs(seed)
	var all []Stamp
	for _, id := range ids {
		all = append(all, ps[id].Log()...)
	}
	return all
}

func randomProcs(seed int64) map[string]*Process {
	net, ps := trio(seed)
	rng := rand.New(rand.NewSource(seed))
	for i := 0; i < 40; i++ {
		p := ps[ids[rng.Intn(3)]]
		if rng.Intn(3) == 0 {
			p.Local("work")
		} else {
			p.SendTo(ids[rng.Intn(3)], fmt.Sprint("m", i))
		}
		net.RunFor(time.Duration(rng.Intn(15)) * time.Millisecond)
	}
	net.RunUntilIdle(10000)
	return ps
}

// Holds: when a happened before b, Lamport(a) < Lamport(b). The vector clock is the ground truth for "happened before".
func TestLamportRespectsCausality(t *testing.T) {
	for seed := int64(1); seed <= 30; seed++ {
		all := randomRun(seed)
		for _, a := range all {
			for _, b := range all {
				if Compare(a.V, b.V) == Before && a.L >= b.L {
					t.Fatalf("seed %d: %s %s (L=%d) happened before %s %s (L=%d)", seed, a.Proc, a.Label, a.L, b.Proc, b.Label, b.L)
				}
			}
		}
	}
}

// Breaks: Lamport order is not causal order. Two events that never heard of each other still get ordered times.
func TestLamportCannotTellConcurrent(t *testing.T) {
	_, ps := trio(1)
	a := ps["A"].Local("write x")
	ps["B"].Local("write y")
	b := ps["B"].Local("write y again")
	if !(a.L < b.L) {
		t.Fatalf("expected Lamport(a)=%d < Lamport(b)=%d", a.L, b.L)
	}
	if got := Compare(a.V, b.V); got != Concurrent {
		t.Fatalf("vector clocks say %v, want concurrent", got)
	}
	t.Logf("Lamport says a (%d) is before b (%d); the vector clocks %v and %v say concurrent", a.L, b.L, a.V, b.V)
}

// Holds: vector clocks mark two writes made without communication as concurrent, and order them once a message links them.
func TestVectorClocksDetectConcurrentWrites(t *testing.T) {
	net, ps := trio(1)
	w1 := ps["A"].Local("x=1")
	w2 := ps["B"].Local("x=2")
	if got := Compare(w1.V, w2.V); got != Concurrent {
		t.Fatalf("got %v, want concurrent", got)
	}
	ps["A"].SendTo("B", "have x=1")
	net.RunUntilIdle(100)
	w3 := ps["B"].Local("x=3")
	if got := Compare(w1.V, w3.V); got != Before {
		t.Fatalf("after the message: got %v, want before", got)
	}
	if got := Compare(w2.V, w3.V); got != Before {
		t.Fatalf("same process: got %v, want before", got)
	}
}

// Each process's own vector clock only grows: every event is after the previous one at the same process.
func TestProcessClocksNeverGoBackwards(t *testing.T) {
	for seed := int64(1); seed <= 10; seed++ {
		for id, p := range randomProcs(seed) {
			log := p.Log()
			for i := 1; i < len(log); i++ {
				if Compare(log[i-1].V, log[i].V) != Before {
					t.Fatalf("seed %d: %s event %d has %v after %v", seed, id, i, log[i].V, log[i-1].V)
				}
			}
		}
	}
}

func TestVectorClockCompareCases(t *testing.T) {
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
	}
	for _, c := range cases {
		if got := Compare(c.a, c.b); got != c.want {
			t.Errorf("Compare(%v, %v) = %v, want %v", c.a, c.b, got, c.want)
		}
	}
}

func TestMergeDoesNotChangeInputs(t *testing.T) {
	a, b := VC{"A": 2}, VC{"A": 1, "B": 3}
	m := Merge(a, b)
	if !reflect.DeepEqual(m, VC{"A": 2, "B": 3}) || !reflect.DeepEqual(a, VC{"A": 2}) || !reflect.DeepEqual(b, VC{"A": 1, "B": 3}) {
		t.Fatalf("merge %v, inputs %v %v", m, a, b)
	}
}

func deliveries(net *simnet.AsyncNet) string {
	var sb strings.Builder
	for _, d := range net.Log() {
		fmt.Fprintf(&sb, "%v %s>%s %v\n", d.At, d.From, d.To, d.Msg.(Msg).Payload)
	}
	return sb.String()
}

func scripted(seed int64) string {
	net, ps := trio(seed)
	for i := 0; i < 10; i++ {
		ps["A"].SendTo("B", fmt.Sprint("a", i))
		ps["B"].SendTo("C", fmt.Sprint("b", i))
		net.RunFor(2 * time.Millisecond)
	}
	net.RunUntilIdle(1000)
	return deliveries(net)
}

// The same seed gives the same message order and times; another seed gives another.
func TestSameSeedSameStamps(t *testing.T) {
	if a, b := scripted(5), scripted(5); a != b {
		t.Fatal("two runs with seed 5 differ")
	}
	if scripted(5) == scripted(6) {
		t.Fatal("seeds 5 and 6 gave the same delivery order")
	}
	if !reflect.DeepEqual(randomRun(3), randomRun(3)) {
		t.Fatal("stamps differ between two runs with the same seed")
	}
}

// Many goroutines use one process at once (run with -race): every stamp is distinct and increasing.
func TestConcurrentUse(t *testing.T) {
	net, ps := trio(1)
	var wg sync.WaitGroup
	for g := 0; g < 40; g++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for i := 0; i < 25; i++ {
				ps["A"].Local("work")
				ps["A"].SendTo("B", "m")
			}
		}()
	}
	wg.Wait()
	net.RunUntilIdle(10000)
	log := ps["A"].Log()
	if len(log) != 2000 {
		t.Fatalf("got %d events, want 2000", len(log))
	}
	for i := 1; i < len(log); i++ {
		if log[i].L != log[i-1].L+1 {
			t.Fatalf("event %d has L=%d after L=%d", i, log[i].L, log[i-1].L)
		}
	}
	if got := len(ps["B"].Log()); got != 1000 {
		t.Fatalf("B received %d messages, want 1000", got)
	}
}

// Breaks: with wall-clock timestamps, a write made after reading another write can get an earlier timestamp.
func TestWallClockInvertsCausalOrder(t *testing.T) {
	net := simnet.NewAsync(1)
	net.SetDelay(5*time.Millisecond, 5*time.Millisecond)
	clockA := SkewedClock{net, 0}
	clockB := SkewedClock{net, -20 * time.Millisecond} // B's clock runs 20 ms behind
	var reg WallRegister
	var first, second WallValue
	net.Register("B", func(string, any) {
		second = reg.Write(clockB, "x=2") // B has seen x=1, so this write is causally later
	})
	first = reg.Write(clockA, "x=1")
	net.Send("A", "B", "x=1 written")
	net.RunUntilIdle(10)
	if !second.TS.Before(first.TS) {
		t.Fatalf("expected the later write to carry the earlier timestamp: %v vs %v", second.TS, first.TS)
	}
	if got := reg.Read().Value; got != "x=1" {
		t.Fatalf("register holds %s, want x=1 (the causally later write was lost)", got)
	}
	t.Logf("x=1 stamped %d ms, then x=2 (made after reading x=1) stamped %d ms; newest timestamp wins, and keeps x=1", first.TS.UnixMilli(), second.TS.UnixMilli())
}

// Holds: a hybrid logical clock gives the later write the larger timestamp even when B's clock is behind.
func TestHybridClockOrderAgreesWithCausality(t *testing.T) {
	for seed := int64(1); seed <= 20; seed++ {
		net := simnet.NewAsync(seed)
		net.SetDelay(1*time.Millisecond, 30*time.Millisecond)
		net.RunFor(time.Second) // start well after the epoch so that skewed clocks are positive
		skew := map[string]time.Duration{"A": 0, "B": -30 * time.Millisecond, "C": 50 * time.Millisecond}
		hlc := map[string]*HLC{}
		var sent, got []HLCTime
		for _, id := range ids {
			id := id
			hlc[id] = NewHLC(SkewedClock{net, skew[id]})
			net.Register(id, func(_ string, msg any) {
				m := msg.(HLCTime)
				got = append(got, hlc[id].Receive(m))
				sent = append(sent, m)
			})
		}
		rng := rand.New(rand.NewSource(seed))
		last := map[string]HLCTime{}
		for i := 0; i < 60; i++ {
			from, to := ids[rng.Intn(3)], ids[rng.Intn(3)]
			ts := hlc[from].Now()
			if !last[from].Less(ts) {
				t.Fatalf("seed %d: %s stamp went backwards: %v after %v", seed, from, ts, last[from])
			}
			last[from] = ts
			net.Send(from, to, ts)
			net.RunFor(time.Duration(rng.Intn(10)) * time.Millisecond)
		}
		net.RunUntilIdle(1000)
		for i := range got {
			if !sent[i].Less(got[i]) {
				t.Fatalf("seed %d: receive stamp %v is not after send stamp %v", seed, got[i], sent[i])
			}
		}
		for _, id := range ids { // the hybrid time stays within the largest clock difference of real time
			phys := net.Now().Add(skew[id]).UnixNano()
			if d := time.Duration(hlc[id].Now().L - phys); d > 80*time.Millisecond || d < -80*time.Millisecond {
				t.Fatalf("seed %d: %s hybrid time is %v away from its own clock", seed, id, d)
			}
		}
	}
}

func TestHLCCounterBreaksTies(t *testing.T) {
	net := simnet.NewAsync(1)
	net.RunFor(time.Second) // the virtual clock then stays still
	h := NewHLC(net)
	a, b := h.Now(), h.Now()
	if a.L != b.L || a.C != 0 || b.C != 1 || !a.Less(b) {
		t.Fatalf("got %v then %v", a, b)
	}
	c := h.Receive(HLCTime{L: a.L, C: 5})
	if c.C != 6 {
		t.Fatalf("receive with equal physical parts: got %v, want counter 6", c)
	}
}

// Holds (no new structure): one writer needs only a sequence number; reordered messages sort back into write order.
func TestSingleWriterSequenceIsEnough(t *testing.T) {
	net := simnet.NewAsync(9)
	net.SetDelay(1*time.Millisecond, 50*time.Millisecond)
	type rec struct {
		Seq uint64
		Val int
	}
	var got []rec
	net.Register("B", func(_ string, m any) { got = append(got, m.(rec)) })
	var seq Seq
	for i := 0; i < 50; i++ {
		net.Send("A", "B", rec{seq.Next(), i})
	}
	net.RunUntilIdle(1000)
	if sort.SliceIsSorted(got, func(i, j int) bool { return got[i].Seq < got[j].Seq }) {
		t.Fatal("expected the messages to arrive out of order with this seed")
	}
	sort.Slice(got, func(i, j int) bool { return got[i].Seq < got[j].Seq })
	for i, r := range got {
		if r.Val != i {
			t.Fatalf("position %d holds value %d", i, r.Val)
		}
	}
}

func TestOverHTTP(t *testing.T) {
	urls := map[string]string{}
	procs := map[string]*Process{}
	for _, id := range []string{"A", "B"} {
		procs[id] = NewProcess(id, &HTTPSender{URLs: urls, Timeout: time.Second})
		srv := httptest.NewServer(HTTPHandler(procs[id]))
		defer srv.Close()
		urls[id] = srv.URL
	}
	w1 := procs["A"].Local("x=1")
	procs["A"].SendTo("B", "m")
	w2 := procs["B"].Local("x=2")
	if got := Compare(w1.V, w2.V); got != Before {
		t.Fatalf("got %v, want before: B has seen A's message", got)
	}
}
