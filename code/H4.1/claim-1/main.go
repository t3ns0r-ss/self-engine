// Claim H4.1.1 check: in every execution of 3 processes with up to 6 events, if event a happened
// before event b then Lamport(a) < Lamport(b). The converse is false: the program also looks for the
// shortest execution with two concurrent events whose Lamport times are nevertheless in order.
package main

import (
	"fmt"

	"selfengine/code/H4.1/execs"
)

func main() {
	violations, shortest := 0, 0
	execs.Enumerate(3, 6, func(x *execs.Execution) {
		for i, a := range x.Events {
			for j, b := range x.Events {
				if x.Before[i][j] && a.L >= b.L {
					violations++
				}
				concurrent := i != j && !x.Before[i][j] && !x.Before[j][i]
				if concurrent && a.L < b.L && (shortest == 0 || len(x.Events) < shortest) {
					shortest = len(x.Events)
				}
			}
		}
	})
	fmt.Printf("a happened before b but Lamport(a) >= Lamport(b): %d cases\n", violations)
	fmt.Printf("fewest events in an execution with concurrent a, b and Lamport(a) < Lamport(b): %d\n", shortest)
}
