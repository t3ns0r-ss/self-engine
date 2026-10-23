package clk

import (
	"math/rand"
	"sync"
	"testing"
	"time"
)

// manual is a clock that moves only when the test says so.
type manual struct {
	mu sync.Mutex
	t  time.Time
}

func (m *manual) Now() time.Time {
	m.mu.Lock()
	defer m.mu.Unlock()
	return m.t
}
func (m *manual) Add(d time.Duration) { m.mu.Lock(); m.t = m.t.Add(d); m.mu.Unlock() }

func at(ms int64) *manual { return &manual{t: time.Unix(0, ms*int64(time.Millisecond))} }

func TestNowFollowsThePhysicalClock(t *testing.T) {
	c := at(1000)
	h := NewHLC(c)
	a := h.Now()
	c.Add(5 * time.Millisecond)
	b := h.Now()
	if a != (HLCTime{1000 * int64(time.Millisecond), 0}) || b != (HLCTime{1005 * int64(time.Millisecond), 0}) {
		t.Fatalf("got %v then %v", a, b)
	}
}

func TestCounterBreaksTiesWhenTheClockStandsStill(t *testing.T) {
	h := NewHLC(at(1000))
	a, b, c := h.Now(), h.Now(), h.Now()
	if a.C != 0 || b.C != 1 || c.C != 2 || a.L != c.L || !a.Less(b) || !b.Less(c) {
		t.Fatalf("got %v %v %v", a, b, c)
	}
}

func TestNeverGoesBackwardsWhenThePhysicalClockDoes(t *testing.T) {
	c := at(1000)
	h := NewHLC(c)
	a := h.Now()
	c.Add(-50 * time.Millisecond) // the machine's clock is stepped back
	b := h.Now()
	if !a.Less(b) {
		t.Fatalf("%v is not after %v", b, a)
	}
}

func TestReceiveFromAFasterClockIsAfterTheSend(t *testing.T) {
	a, b := NewHLC(at(1050)), NewHLC(at(1000)) // B's clock is 50 ms behind
	sent := a.Now()
	got := b.Receive(sent)
	if !sent.Less(got) {
		t.Fatalf("receive %v is not after send %v", got, sent)
	}
	next := b.Now()
	if !got.Less(next) {
		t.Fatalf("B's next stamp %v is not after its receive %v", next, got)
	}
}

func TestOrderAgreesWithCausalityAcrossSkewedClocks(t *testing.T) {
	skew := []int64{0, -30, 50} // ms
	for seed := int64(1); seed <= 20; seed++ {
		rng := rand.New(rand.NewSource(seed))
		base := at(10_000)
		clocks := make([]*manual, 3)
		hlc := make([]*HLC, 3)
		for i := range hlc {
			clocks[i] = at(10_000 + skew[i])
			hlc[i] = NewHLC(clocks[i])
		}
		last := make([]HLCTime, 3)
		for step := 0; step < 200; step++ {
			for _, c := range append(clocks, base) {
				c.Add(time.Duration(rng.Intn(3)) * time.Millisecond)
			}
			from, to := rng.Intn(3), rng.Intn(3)
			sent := hlc[from].Now()
			if !last[from].Less(sent) {
				t.Fatalf("seed %d: node %d went backwards: %v after %v", seed, from, sent, last[from])
			}
			last[from] = sent
			got := hlc[to].Receive(sent)
			if !sent.Less(got) || (to != from && !last[to].Less(got)) {
				t.Fatalf("seed %d: receive %v is not after send %v and the last stamp %v", seed, got, sent, last[to])
			}
			last[to] = got
		}
	}
}

func TestHybridTimeStaysNearThePhysicalTime(t *testing.T) {
	a, b := at(5000), at(5000-30)
	ha, hb := NewHLC(a), NewHLC(b)
	for i := 0; i < 100; i++ {
		a.Add(time.Millisecond)
		b.Add(time.Millisecond)
		hb.Receive(ha.Now())
	}
	got := time.Duration(hb.Now().L - b.Now().UnixNano())
	if got > 31*time.Millisecond {
		t.Fatalf("B's hybrid time is %v ahead of its own clock; it should stay within the 30 ms difference between the clocks", got)
	}
}

func TestConcurrentStamps(t *testing.T) {
	h := NewHLC(at(1000))
	var wg sync.WaitGroup
	var mu sync.Mutex
	seen := map[HLCTime]bool{}
	for g := 0; g < 20; g++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for i := 0; i < 50; i++ {
				s := h.Now()
				mu.Lock()
				if seen[s] {
					t.Errorf("duplicate stamp %v", s)
				}
				seen[s] = true
				mu.Unlock()
			}
		}()
	}
	wg.Wait()
	if len(seen) != 1000 {
		t.Fatalf("%d distinct stamps, want 1000", len(seen))
	}
}
