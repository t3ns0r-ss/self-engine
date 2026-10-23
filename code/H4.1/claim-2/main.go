// Claim H4.1.2 check: in every execution of 3 processes with up to 6 events, comparing the vector
// clocks of two events gives exactly the happened-before relation: Before when a happened before b,
// After when b happened before a, Concurrent when neither did.
package main

import (
	"fmt"

	"selfengine/code/H4.1/execs"
	clocks "selfengine/code/H4.1/lab-clocks"
)

func main() {
	pairs, wrong, concurrent := 0, 0, 0
	execs.Enumerate(3, 6, func(x *execs.Execution) {
		for i, a := range x.Events {
			for j, b := range x.Events {
				if i >= j {
					continue
				}
				pairs++
				want := clocks.Concurrent
				switch {
				case x.Before[i][j]:
					want = clocks.Before
				case x.Before[j][i]:
					want = clocks.After
				}
				if want == clocks.Concurrent {
					concurrent++
				}
				if got := clocks.Compare(a.V, b.V); got != want {
					wrong++
				}
			}
		}
	})
	fmt.Printf("pairs where Compare disagrees with happened-before: %d\n", wrong)
	fmt.Printf("some pairs were concurrent, so the Concurrent answer was exercised: %t\n", concurrent > 0)
	fmt.Printf("some pairs were checked: %t\n", pairs > 0)
}
