package clk

import (
	"reflect"
	"testing"
)

// A at 1000 ms writes x=1; B, 20 ms behind, reads it and writes x=2 at what its clock calls 990 ms.
func skewed() []Write {
	a, b := NewProcess("A"), NewProcess("B")
	w1 := a.Local("x=1")
	m := a.Send("x=1")
	b.Receive(m)
	w2 := b.Local("x=2")
	return []Write{{"A", 1000, w1.V}, {"B", 990, w2.V}}
}

func TestInversionsFindsSkewedWrites(t *testing.T) {
	got := Inversions(skewed())
	if !reflect.DeepEqual(got, [][2]int{{0, 1}}) {
		t.Fatalf("got %v, want [[0 1]]: write 0 is causally before write 1 but has the larger timestamp", got)
	}
}

func TestInversionsEmptyWhenClocksAgree(t *testing.T) {
	ws := skewed()
	ws[1].TS = 1005
	if got := Inversions(ws); len(got) != 0 {
		t.Fatalf("got %v, want none", got)
	}
}

func TestEqualTimestampsCountAsInversion(t *testing.T) {
	ws := skewed()
	ws[1].TS = ws[0].TS // a tie cannot say which write is later
	if got := Inversions(ws); len(got) != 1 {
		t.Fatalf("got %v, want one pair", got)
	}
}

func TestConcurrentWritesAreNeverInversions(t *testing.T) {
	a, b := NewProcess("A"), NewProcess("B")
	ws := []Write{{"A", 1000, a.Local("x=1").V}, {"B", 900, b.Local("x=2").V}}
	if got := Inversions(ws); len(got) != 0 {
		t.Fatalf("got %v: concurrent writes have no causal order to contradict", got)
	}
}

func TestInversionsAreOrdered(t *testing.T) {
	a := NewProcess("A")
	w1, w2, w3 := a.Local("1"), a.Local("2"), a.Local("3")
	ws := []Write{{"A", 10, w3.V}, {"A", 20, w2.V}, {"A", 30, w1.V}} // timestamps run backwards
	want := [][2]int{{1, 0}, {2, 0}, {2, 1}}
	if got := Inversions(ws); !reflect.DeepEqual(got, want) {
		t.Fatalf("got %v, want %v", got, want)
	}
}

func TestWallWinnerKeepsTheLaterWriteWhenClocksAgree(t *testing.T) {
	ws := skewed()
	ws[1].TS = 1005
	if w := WallWinner(ws); w != 1 || WinnerIsStale(ws) {
		t.Fatalf("winner %d, stale %v; want write 1 and not stale", w, WinnerIsStale(ws))
	}
}

func TestWallWinnerLosesTheCausallyLaterWrite(t *testing.T) {
	ws := skewed()
	if w := WallWinner(ws); w != 0 {
		t.Fatalf("winner %d, want 0 (timestamp 1000 beats 990)", w)
	}
	if !WinnerIsStale(ws) {
		t.Fatal("the winner happened before the other write, so it is stale")
	}
}

func TestWallWinnerEdgeCases(t *testing.T) {
	if WallWinner(nil) != -1 || WinnerIsStale(nil) {
		t.Fatal("an empty list has no winner")
	}
	ws := []Write{{"A", 5, VC{"A": 1}}, {"B", 5, VC{"B": 1}}}
	if WallWinner(ws) != 0 {
		t.Fatalf("ties go to the lowest index, got %d", WallWinner(ws))
	}
	if WinnerIsStale(ws) {
		t.Fatal("concurrent writes: the winner is not causally before the other")
	}
}
