package clk

import (
	"math/rand"
	"reflect"
	"sync"
	"testing"
)

func TestSeqCountsFromOne(t *testing.T) {
	var s Seq
	if a, b, c := s.Next(), s.Next(), s.Next(); a != 1 || b != 2 || c != 3 {
		t.Fatalf("got %d %d %d", a, b, c)
	}
}

func TestSeqIsUniqueUnderConcurrency(t *testing.T) {
	var s Seq
	var wg sync.WaitGroup
	var mu sync.Mutex
	seen := map[uint64]bool{}
	for g := 0; g < 20; g++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for i := 0; i < 100; i++ {
				n := s.Next()
				mu.Lock()
				if seen[n] {
					t.Errorf("number %d handed out twice", n)
				}
				seen[n] = true
				mu.Unlock()
			}
		}()
	}
	wg.Wait()
	if len(seen) != 2000 {
		t.Fatalf("%d distinct numbers, want 2000", len(seen))
	}
}

func records(n int) []Rec {
	var s Seq
	out := make([]Rec, n)
	for i := range out {
		out[i] = Rec{s.Next(), string(rune('a' + i%26))}
	}
	return out
}

func TestInOrderRestoresTheWriteOrder(t *testing.T) {
	want := records(50)
	got := append([]Rec(nil), want...)
	rand.New(rand.NewSource(3)).Shuffle(len(got), func(i, j int) { got[i], got[j] = got[j], got[i] })
	shuffled := append([]Rec(nil), got...)
	if out := InOrder(got); !reflect.DeepEqual(out, want) {
		t.Fatalf("got %v", out)
	}
	if !reflect.DeepEqual(got, shuffled) {
		t.Fatal("InOrder changed its input")
	}
}

func TestInOrderDropsDuplicates(t *testing.T) {
	in := []Rec{{2, "b"}, {1, "a"}, {2, "b"}, {3, "c"}, {1, "a"}}
	want := []Rec{{1, "a"}, {2, "b"}, {3, "c"}}
	if out := InOrder(in); !reflect.DeepEqual(out, want) {
		t.Fatalf("got %v", out)
	}
	if out := InOrder(nil); len(out) != 0 {
		t.Fatalf("empty input gave %v", out)
	}
}

func TestGapsShowMissingRecords(t *testing.T) {
	cases := []struct {
		in   []Rec
		want []uint64
	}{
		{nil, nil},
		{[]Rec{{1, "a"}, {2, "b"}, {3, "c"}}, nil},
		{[]Rec{{1, "a"}, {4, "d"}}, []uint64{2, 3}},
		{[]Rec{{3, "c"}}, []uint64{1, 2}},
		{[]Rec{{5, "e"}, {2, "b"}, {1, "a"}, {2, "b"}}, []uint64{3, 4}},
	}
	for _, c := range cases {
		if got := Gaps(c.in); !reflect.DeepEqual(got, c.want) {
			t.Errorf("Gaps(%v) = %v, want %v", c.in, got, c.want)
		}
	}
}
