package kv

import (
	"errors"
	"fmt"
	"sync"
	"testing"
)

var _ = errors.Is
var _ = fmt.Sprint
var _ sync.Mutex

func TestPutThenGet(t *testing.T) {
	_, w, r := newCluster(2, 2)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	got, err := r.Get("k")
	if err != nil || got != (Versioned{"v1", 1}) {
		t.Fatalf("got %v, %v; want v1", got, err)
	}
}

func TestUnknownKeyReadsEmpty(t *testing.T) {
	_, _, r := newCluster(2, 2)
	got, err := r.Get("nothing")
	if err != nil || got != (Versioned{}) {
		t.Fatalf("got %v, %v; want the zero Versioned", got, err)
	}
}

func TestGetReturnsNewestOfReplies(t *testing.T) {
	net, _, r := newCluster(2, 2)
	net.Call("x", "C", PutReq{"k", Versioned{"v2", 2}}) // only C holds version 2
	net.Call("x", "A", PutReq{"k", Versioned{"v1", 1}})
	net.Call("x", "B", PutReq{"k", Versioned{"v1", 1}})
	got, err := r.Get("k")
	if err != nil || got.Value != "v2" {
		t.Fatalf("got %v, %v; want v2 from the one replica that has it", got, err)
	}
}

func TestOlderVersionDoesNotOverwrite(t *testing.T) {
	_, w, r := newCluster(2, 2)
	w.Put("k", Versioned{"v2", 2})
	w.Put("k", Versioned{"v1", 1})
	got, err := r.Get("k")
	if err != nil || got.Value != "v2" {
		t.Fatalf("got %v, %v; want v2", got, err)
	}
}

func TestConcurrentClients(t *testing.T) {
	net, _, _ := newCluster(2, 2)
	var wg sync.WaitGroup
	for i := 0; i < 40; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			c := &Client{Net: net, ID: fmt.Sprintf("c%d", i), Replicas: ids, W: 2, R: 2}
			if err := c.Put("shared", Versioned{fmt.Sprint("v", i+1), uint64(i + 1)}); err != nil {
				t.Error(err)
			}
		}()
	}
	wg.Wait()
	_, _, r := newCluster(2, 2)
	r.Net = net
	got, err := r.Get("shared")
	if err != nil || got.Version != 40 {
		t.Fatalf("got %v, %v; want version 40", got, err)
	}
}
