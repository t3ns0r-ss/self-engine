package kv

// Choice is a quorum setting for N = 3 replicas.
type Choice struct {
	W, R       int
	ReadRepair bool
}

// Choose returns the setting for a workload that can tolerate stale reads for toleratedStalenessMs.
// Below 1000 ms: W = 2, R = 2, no read repair. At 1000 ms or more: W = 2, R = 1, with read repair.
func Choose(toleratedStalenessMs int) Choice {
	if toleratedStalenessMs > 1000 {
		return Choice{W: 2, R: 1, ReadRepair: true}
	}
	return Choice{W: 2, R: 2}
}
