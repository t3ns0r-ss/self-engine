// Command node runs one quorum replica as an HTTP server: go run ./H4.2/lab-quorumkv/cmd/node -listen 127.0.0.1:8001
package main

import (
	"flag"
	"log"
	"net/http"

	"selfengine/code/H4.2/lab-quorumkv"
)

func main() {
	listen := flag.String("listen", "127.0.0.1:8001", "address to listen on")
	flag.Parse()
	log.Fatal(http.ListenAndServe(*listen, quorumkv.HTTPHandler(quorumkv.NewStandaloneReplica())))
}
