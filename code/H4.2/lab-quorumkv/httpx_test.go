package quorumkv

import (
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
