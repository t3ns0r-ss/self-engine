package capcalc

import (
	"math"
	"testing"
)

func near(a, b float64) bool { return math.Abs(a-b) <= 1e-9*math.Max(1, math.Abs(b)) }

func TestRatesAndStorage(t *testing.T) {
	// 20 million uploads a day is 231.48... per second; peak factor 3 gives 694.44...
	avg := PerSecond(20_000_000)
	if !near(avg, 20_000_000.0/86_400) {
		t.Fatalf("avg = %v", avg)
	}
	if got := Format(Peak(avg, 3), 4); got != "694.4" {
		t.Fatalf("peak = %s, want 694.4", got)
	}
	// 20 M items x 2 MB x 365 days x 1 copy = 14.6 PB
	if got := Storage(20_000_000, 2*MB, 365, 1) / PB; !near(got, 14.6) {
		t.Fatalf("storage = %v PB", got)
	}
	if got := Bandwidth(100, 2*KB); !near(got, 200_000) {
		t.Fatalf("bandwidth = %v", got)
	}
}

func TestMachinesAndQueues(t *testing.T) {
	if got := Machines(1000, 300, 0.3); got != 5 { // 300 x 0.7 = 210 per machine; 1000/210 = 4.76
		t.Fatalf("machines = %d, want 5", got)
	}
	if Machines(1, 0, 0.1) != -1 || Machines(1, 1, 1) != -1 {
		t.Fatal("invalid inputs must return -1")
	}
	if !near(LittleL(100, 0.2), 20) {
		t.Fatal("Little's law")
	}
	if !near(MM1Wait(50, 100), 0.02) || !math.IsInf(MM1Wait(100, 100), 1) {
		t.Fatal("M/M/1 wait")
	}
	if !near(Utilization(50, 100), 0.5) {
		t.Fatal("utilization")
	}
}

func TestAvailabilityAndQuorum(t *testing.T) {
	if got := DowntimePerYear(0.999) / 3600; math.Abs(got-8.76) > 1e-6 {
		t.Fatalf("0.999 allows %v hours a year, want 8.76", got)
	}
	if got := SeriesAvailability(0.99, 0.99); !near(got, 0.9801) {
		t.Fatalf("series = %v", got)
	}
	if got := ParallelAvailability(0.99, 0.99); !near(got, 0.9999) {
		t.Fatalf("parallel = %v", got)
	}
	if !QuorumOverlaps(3, 2, 2) || QuorumOverlaps(3, 1, 1) {
		t.Fatal("quorum overlap")
	}
	if Round(123456, 2) != 120000 || Round(0.012345, 2) != 0.012 {
		t.Fatal("round")
	}
}
