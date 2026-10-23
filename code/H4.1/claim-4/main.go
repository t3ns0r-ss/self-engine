// Claim H4.1.4 check (seeded simulation): two machines whose clocks are off by independent amounts
// drawn evenly from -10 ms to +10 ms. A writes; B reads that write and writes 5 ms later (causally after).
// With wall-clock timestamps the later write is stamped earlier in about 28.125% of trials; with the
// hybrid clock it never is.
package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"

	clocks "selfengine/code/H4.1/lab-clocks"
)

type fixed struct{ t time.Time }

func (f *fixed) Now() time.Time { return f.t }

func main() {
	const trials, seed, gap = 200000, 1, 5 * time.Millisecond
	rng := rand.New(rand.NewSource(seed))
	offset := func() time.Duration { return time.Duration((rng.Float64()*20 - 10) * float64(time.Millisecond)) }
	wallLost, hybridLost := 0, 0
	for i := 0; i < trials; i++ {
		base := &fixed{time.Unix(1000, 0)}
		a := clocks.SkewedClock{Base: base, Offset: offset()}
		b := clocks.SkewedClock{Base: base, Offset: offset()}
		var reg clocks.WallRegister
		reg.Write(a, "a")
		hA, hB := clocks.NewHLC(a), clocks.NewHLC(b)
		stampA := hA.Now()
		base.t = base.t.Add(gap)
		reg.Write(b, "b")
		if reg.Read().Value != "b" {
			wallLost++
		}
		if !stampA.Less(hB.Receive(stampA)) {
			hybridLost++
		}
	}
	p := float64(wallLost) / trials
	fmt.Printf("analytic probability the later write is stamped earlier: 0.28125\n")
	fmt.Printf("wall-clock simulation within 0.005 of the analytic value: %t\n", math.Abs(p-0.28125) < 0.005)
	fmt.Printf("hybrid clock: later write stamped earlier in %d of %d trials\n", hybridLost, trials)
}
