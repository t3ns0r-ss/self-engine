// Command client does one put or get against the quorum nodes:
//
//	go run ./H4.2/lab-quorumkv/cmd/client -nodes A=127.0.0.1:7001,B=127.0.0.1:7002,C=127.0.0.1:7003 -w 2 -r 2 put k v1 1
//	go run ./H4.2/lab-quorumkv/cmd/client -nodes ... get k
package main

import (
	"flag"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
	"time"

	"selfengine/code/H4.2/lab-quorumkv"
)

func main() {
	nodes := flag.String("nodes", "", "comma-separated id=host:port list")
	w := flag.Int("w", 2, "write quorum")
	r := flag.Int("r", 2, "read quorum")
	repair := flag.Bool("repair", false, "read repair")
	timeout := flag.Duration("timeout", 500*time.Millisecond, "per-node timeout")
	flag.Parse()
	urls := map[string]string{}
	for _, kv := range strings.Split(*nodes, ",") {
		id, addr, ok := strings.Cut(kv, "=")
		if !ok {
			fmt.Fprintln(os.Stderr, "bad -nodes entry:", kv)
			os.Exit(2)
		}
		urls[id] = "http://" + addr
	}
	var ids []string
	for id := range urls {
		ids = append(ids, id)
	}
	sort.Strings(ids)
	c := &quorumkv.Client{Net: &quorumkv.HTTPCaller{URLs: urls, Timeout: *timeout}, ID: "cli", Replicas: ids, W: *w, R: *r, ReadRepair: *repair}
	args := flag.Args()
	switch {
	case len(args) == 4 && args[0] == "put":
		ver, err := strconv.ParseUint(args[3], 10, 64)
		if err != nil {
			fmt.Fprintln(os.Stderr, "version must be a number:", err)
			os.Exit(2)
		}
		if err := c.Put(args[1], quorumkv.Versioned{Value: args[2], Version: ver}); err != nil {
			fmt.Println("put failed:", err)
			os.Exit(1)
		}
		fmt.Println("put ok")
	case len(args) == 2 && args[0] == "get":
		v, err := c.Get(args[1])
		if err != nil {
			fmt.Println("get failed:", err)
			os.Exit(1)
		}
		fmt.Printf("get %s = %q (version %d)\n", args[1], v.Value, v.Version)
	default:
		fmt.Fprintln(os.Stderr, "usage: client [flags] put KEY VALUE VERSION | get KEY")
		os.Exit(2)
	}
}
