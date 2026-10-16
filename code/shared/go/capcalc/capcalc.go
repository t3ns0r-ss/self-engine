// Package capcalc holds the arithmetic that estimation (calc) programs share, so each program shows its
// inputs and formulas and the library supplies only unit conversions and standard formulas.
// Every function is pure: same inputs, same output. Rounding happens only when printing (see Round).
package capcalc

import (
	"math"
	"strconv"
)

// Time and size constants, so calc programs do not repeat magic numbers.
const (
	SecondsPerDay  = 86_400
	SecondsPerYear = 365 * SecondsPerDay
	KB             = 1e3 // decimal units, as network and storage vendors use them
	MB             = 1e6
	GB             = 1e9
	TB             = 1e12
	PB             = 1e15
)

// PerSecond converts a count per day into an average rate per second.
func PerSecond(perDay float64) float64 { return perDay / SecondsPerDay }

// Peak applies a peak factor (peak-hour rate divided by the daily average rate).
func Peak(avgRate, factor float64) float64 { return avgRate * factor }

// Bandwidth is bytes per second for a rate of items of a given size.
func Bandwidth(itemsPerSecond, bytesPerItem float64) float64 { return itemsPerSecond * bytesPerItem }

// Storage is the bytes accumulated over days by itemsPerDay items of bytesPerItem each, with replicas copies.
func Storage(itemsPerDay, bytesPerItem float64, days int, replicas int) float64 {
	return itemsPerDay * bytesPerItem * float64(days) * float64(replicas)
}

// Machines is how many machines are needed for load when one machine handles perMachine, rounded up.
// headroom is the fraction of capacity that must stay free (0.3 means run at most 70% busy).
func Machines(load, perMachine, headroom float64) int {
	if perMachine <= 0 || headroom < 0 || headroom >= 1 {
		return -1
	}
	return int(math.Ceil(load / (perMachine * (1 - headroom))))
}

// LittleL is Little's law: the average number in a system L = arrival rate x average time in the system.
func LittleL(arrivalRate, secondsInSystem float64) float64 { return arrivalRate * secondsInSystem }

// MM1Wait is the mean time in system (waiting plus service) of an M/M/1 queue, in seconds,
// for arrival rate lambda and service rate mu, both per second. It is +Inf when lambda >= mu (no steady state).
func MM1Wait(lambda, mu float64) float64 {
	if lambda >= mu {
		return math.Inf(1)
	}
	return 1 / (mu - lambda)
}

// Utilization is lambda / mu.
func Utilization(lambda, mu float64) float64 { return lambda / mu }

// DowntimePerYear is the seconds of allowed downtime per year for an availability such as 0.999.
func DowntimePerYear(availability float64) float64 { return (1 - availability) * SecondsPerYear }

// SeriesAvailability is the availability of components that must all work (the product).
func SeriesAvailability(a ...float64) float64 {
	p := 1.0
	for _, x := range a {
		p *= x
	}
	return p
}

// ParallelAvailability is the availability of redundant components where one working is enough.
func ParallelAvailability(a ...float64) float64 {
	q := 1.0
	for _, x := range a {
		q *= 1 - x
	}
	return 1 - q
}

// QuorumOverlaps reports whether any read set of r nodes must intersect any write set of w nodes among n.
func QuorumOverlaps(n, w, r int) bool { return w+r > n }

// Round rounds x to the given number of significant digits; use it only for the printed value.
func Round(x float64, digits int) float64 {
	if x == 0 || math.IsInf(x, 0) || math.IsNaN(x) {
		return x
	}
	p := math.Pow(10, float64(digits)-math.Ceil(math.Log10(math.Abs(x))))
	return math.Round(x*p) / p
}

// Format prints x with the given significant digits and no exponent for ordinary sizes.
func Format(x float64, digits int) string {
	return strconv.FormatFloat(Round(x, digits), 'f', -1, 64)
}
