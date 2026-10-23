// Command node runs one clock process over HTTP:
//
//	go run ./H4.1/lab-clocks/cmd/node -id A -listen 127.0.0.1:8001 -peers B=http://127.0.0.1:8002,C=http://127.0.0.1:8003
package main

import (
	"flag"
	"log"
	"net/http"
	"strings"
	"time"

	clocks "selfengine/code/H4.1/lab-clocks"
)

func main() {
	id := flag.String("id", "A", "process id")
	listen := flag.String("listen", "127.0.0.1:8001", "address to listen on")
	peers := flag.String("peers", "", "comma-separated id=baseURL pairs")
	flag.Parse()
	urls := map[string]string{}
	for _, p := range strings.Split(*peers, ",") {
		if k, v, ok := strings.Cut(p, "="); ok {
			urls[k] = v
		}
	}
	proc := clocks.NewProcess(*id, &clocks.HTTPSender{URLs: urls, Timeout: 500 * time.Millisecond})
	log.Fatal(http.ListenAndServe(*listen, clocks.HTTPHandler(proc)))
}
