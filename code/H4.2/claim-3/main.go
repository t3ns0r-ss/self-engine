// Claim H4.2.3 check: three replicas hold version 1 of a key; a second write (version 2) reached every
// replica except possibly one (the one that was down). A read that contacts all three replicas with read
// repair on leaves all three holding version 2, in every case. Without repair, they agree only when no
// replica missed the write.
package main

import (
	"fmt"

	"selfengine/code/H4.2/lab-quorumkv"
	"selfengine/code/shared/go/simnet"
)

func agree(net *simnet.Net, ids []string) bool {
	first := quorumkv.Snapshot(net, ids[0], "k")
	for _, id := range ids[1:] {
		if quorumkv.Snapshot(net, id, "k") != first {
			return false
		}
	}
	return true
}

// run sets up the cluster, makes `missed` (or nobody, if "") miss version 2, then reads with or without repair.
func run(missed string, repair bool) bool {
	ids := []string{"A", "B", "C"}
	net := simnet.New()
	for _, id := range ids {
		quorumkv.NewReplica(net, id)
	}
	w := &quorumkv.Client{Net: net, ID: "writer", Replicas: ids, W: 2, R: 3}
	r := &quorumkv.Client{Net: net, ID: "reader", Replicas: ids, W: 2, R: 3, ReadRepair: repair}
	w.Put("k", quorumkv.Versioned{Value: "v1", Version: 1})
	if missed != "" {
		net.SetDown(missed, true)
	}
	w.Put("k", quorumkv.Versioned{Value: "v2", Version: 2})
	if missed != "" {
		net.SetDown(missed, false)
	}
	r.Get("k")
	return agree(net, ids)
}

func main() {
	for _, missed := range []string{"", "A", "B", "C"} {
		name := missed
		if name == "" {
			name = "none"
		}
		fmt.Printf("missed=%s: agree_without_repair=%t agree_with_repair=%t\n", name, run(missed, false), run(missed, true))
	}
}
