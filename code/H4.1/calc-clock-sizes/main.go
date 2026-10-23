// Calc H4.1: how big the clocks are and how much clock skew it takes to misorder two writes.
// Inputs are given in the lesson: 8-byte counters and ids, 1 000 000 keys, two causally ordered writes
// 5 ms apart, clock offsets drawn evenly from -10 ms to +10 ms for each machine.
package main

import (
	"fmt"

	"selfengine/code/shared/go/capcalc"
)

// inversion is the chance that the later write gets the smaller wall-clock timestamp when the two
// machines' offsets are independent and uniform on [-s, s] and the writes are gap apart in real time.
// The difference of the offsets is triangular on [-2s, 2s]; the later write is stamped earlier when
// that difference is below -gap, which has probability (2s - gap)^2 / (2 (2s)^2) for gap < 2s.
func inversion(s, gap float64) float64 {
	return (2*s - gap) * (2*s - gap) / (2 * 2 * s * 2 * s)
}

func main() {
	const counter, id, keys = 8.0, 8.0, 1_000_000.0
	fmt.Printf("vc_bytes_20_writers = %s bytes\n", capcalc.Format(20*counter, 4))
	fmt.Printf("vc_bytes_with_ids_20_writers = %s bytes\n", capcalc.Format(20*(counter+id), 4))
	fmt.Printf("vc_bytes_50_writers = %s bytes\n", capcalc.Format(50*counter, 4))
	fmt.Printf("lamport_bytes = %s bytes\n", capcalc.Format(counter, 4))
	fmt.Printf("vc_metadata_1m_keys_20_writers = %s MB\n", capcalc.Format(keys*20*counter/capcalc.MB, 4))
	fmt.Printf("lamport_metadata_1m_keys = %s MB\n", capcalc.Format(keys*counter/capcalc.MB, 4))
	const gapMs = 5.0
	fmt.Printf("skew_to_misorder_5ms = %s ms\n", capcalc.Format(gapMs, 4))
	fmt.Printf("misorder_probability_skew10ms_gap5ms = %s\n", capcalc.Format(inversion(10, gapMs), 5))
}
