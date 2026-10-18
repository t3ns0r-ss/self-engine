// Claim H4.2.1 check: for every N from 1 to 5 and every W, R from 1 to N, every write set of
// size W meets every read set of size R exactly when W + R > N. Prints the number of
// (W, R) pairs where the two disagree; the proof says 0 for every N.
package main

import "fmt"

// subsets returns every subset of {0..n-1} with exactly k members, as bit masks.
func subsets(n, k int) []uint {
	var out []uint
	for m := uint(0); m < 1<<n; m++ {
		bits := 0
		for x := m; x > 0; x &= x - 1 {
			bits++
		}
		if bits == k {
			out = append(out, m)
		}
	}
	return out
}

func main() {
	for n := 1; n <= 5; n++ {
		mismatches := 0
		for w := 1; w <= n; w++ {
			for r := 1; r <= n; r++ {
				always := true
				for _, ws := range subsets(n, w) {
					for _, rs := range subsets(n, r) {
						if ws&rs == 0 {
							always = false
						}
					}
				}
				if always != (w+r > n) {
					mismatches++
				}
			}
		}
		fmt.Printf("N=%d: mismatches with W+R>N rule = %d\n", n, mismatches)
	}
}
