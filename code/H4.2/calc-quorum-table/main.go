// Calc H4.2: availability of quorum setups, replication traffic, and the chance a W=1, R=1 read is stale.
// Assumption stated in the lesson: replicas fail independently, each up with probability 0.999.
package main

import (
	"fmt"
	"math"

	"selfengine/code/shared/go/capcalc"
)

// atLeast is P(at least k of n replicas are up) = sum over i from k to n of C(n,i) p^i (1-p)^(n-i).
func atLeast(n, k int, p float64) float64 {
	total := 0.0
	for i := k; i <= n; i++ {
		c := 1.0
		for j := 1; j <= i; j++ {
			c = c * float64(n-i+j) / float64(j)
		}
		total += c * math.Pow(p, float64(i)) * math.Pow(1-p, float64(n-i))
	}
	return total
}

func main() {
	const up = 0.999
	const minutesPerMonth = 30 * 24 * 60
	setups := []struct {
		name string
		n, k int
	}{{"machine1", 1, 1}, {"n3w2r2", 3, 2}, {"n5w3r3", 5, 3}}
	for _, s := range setups {
		a := atLeast(s.n, s.k, up)
		fmt.Printf("availability_%s = %s\n", s.name, capcalc.Format(a, 9))
		fmt.Printf("downtime_%s = %s minutes per 30-day month\n", s.name, capcalc.Format((1-a)*minutesPerMonth, 4))
	}

	// Replication traffic: every write is sent to all N replicas.
	writesPerSecond, bytesPerWrite, n := 20000.0, 1000.0, 3.0
	ingress := capcalc.Bandwidth(writesPerSecond, bytesPerWrite)
	fmt.Printf("write_ingress = %s MB/s\n", capcalc.Format(ingress/capcalc.MB, 4))
	fmt.Printf("replica_traffic_n3 = %s MB/s\n", capcalc.Format(ingress*n/capcalc.MB, 4))

	// Review twist: 8 000 writes/s of 2 KB to N = 5 replicas.
	fmt.Printf("replica_traffic_n5_8000w = %s MB/s\n", capcalc.Format(capcalc.Bandwidth(8000, 2000)*5/capcalc.MB, 4))

	// W = 3 of N = 3: a write needs every replica up, so write availability is 0.999^3.
	allUp := atLeast(3, 3, up)
	fmt.Printf("write_availability_n3w3 = %s\n", capcalc.Format(allUp, 9))
	fmt.Printf("write_downtime_n3w3 = %s minutes per 30-day month\n", capcalc.Format((1-allUp)*minutesPerMonth, 4))

	// W=1, R=1, N=3: the write has reached 2 replicas, one lags; a read asks one replica chosen evenly.
	fmt.Printf("stale_read_probability_w1r1_one_lagging = %s\n", capcalc.Format(1.0/3.0, 4))
}
