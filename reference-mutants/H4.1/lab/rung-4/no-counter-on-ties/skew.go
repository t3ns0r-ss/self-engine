package clk

// Write is a value written at a node, with the writer's wall-clock timestamp (milliseconds) and
// the writer's vector clock at the time of the write.
type Write struct {
	Node string
	TS   int64
	V    VC
}

// Inversions returns every pair (i, j) where ws[i] happened before ws[j] by their vector clocks but
// ws[i].TS >= ws[j].TS: the wall clock says the causally later write was not later. Pairs are
// ordered by i, then j.
func Inversions(ws []Write) [][2]int {
	var out [][2]int
	for i := range ws {
		for j := range ws {
			if i != j && Compare(ws[i].V, ws[j].V) == Before && ws[i].TS >= ws[j].TS {
				out = append(out, [2]int{i, j})
			}
		}
	}
	return out
}

// WallWinner returns the index of the write that last-write-wins keeps: the highest TS, and the
// lowest index among equal timestamps. It returns -1 for an empty list.
func WallWinner(ws []Write) int {
	best := -1
	for i, w := range ws {
		if best < 0 || w.TS > ws[best].TS {
			best = i
		}
	}
	return best
}

// WinnerIsStale reports whether the write kept by WallWinner happened before another write,
// that is, whether last-write-wins threw away a causally later write.
func WinnerIsStale(ws []Write) bool {
	w := WallWinner(ws)
	for j := range ws {
		if w >= 0 && j != w && Compare(ws[w].V, ws[j].V) == Before {
			return true
		}
	}
	return false
}
