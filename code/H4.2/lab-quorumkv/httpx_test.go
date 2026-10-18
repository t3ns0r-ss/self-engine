package quorumkv

import (
	"net/http"
	"net/http/httptest"
	"testing"
	"time"
)

// The same Client works over real HTTP: three httptest servers stand in for three node processes.
func TestOverHTTP(t *testing.T) {
	urls := map[string]string{}
	var ids []string
	for _, id := range []string{"A", "B", "C"} {
		srv := httptest.NewServer(HTTPHandler(&Replica{data: map[string]Versioned{}}))
		defer srv.Close()
		urls[id] = srv.URL
		ids = append(ids, id)
	}
	c := &Client{Net: &HTTPCaller{URLs: urls, Timeout: time.Second}, ID: "cli", Replicas: ids, W: 2, R: 2}
	if err := c.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	got, err := c.Get("k")
	if err != nil || got.Value != "v1" {
		t.Fatalf("got %v, %v; want v1", got, err)
	}
}

// A node that accepts and never answers (what faultproxy's /blackhole does) must count as down:
// with W = 2 the two healthy nodes are enough, and the call returns after about one timeout.
func TestBlackholedNodeCountsAsDown(t *testing.T) {
	hang := make(chan struct{})
	black := httptest.NewServer(http.HandlerFunc(func(http.ResponseWriter, *http.Request) { <-hang }))
	defer black.Close()
	defer close(hang) // runs first: lets the stuck handlers return so Close can finish
	urls := map[string]string{"C": black.URL}
	ids := []string{"A", "B", "C"}
	for _, id := range ids[:2] {
		srv := httptest.NewServer(HTTPHandler(NewStandaloneReplica()))
		defer srv.Close()
		urls[id] = srv.URL
	}
	c := &Client{Net: &HTTPCaller{URLs: urls, Timeout: 200 * time.Millisecond}, ID: "cli", Replicas: ids, W: 2, R: 2}
	start := time.Now()
	if err := c.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	if took := time.Since(start); took > 2*time.Second {
		t.Fatalf("put took %v; the blackholed node was waited for", took)
	}
}
