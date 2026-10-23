package clk

import (
	"testing"
	"time"
)

func TestReceiveCases(t *testing.T) {
	ms := int64(time.Millisecond)
	check := func(name string, got, want HLCTime) {
		t.Helper()
		if got != want {
			t.Errorf("%s: got %v, want %v", name, got, want)
		}
	}
	// the physical clock is ahead of the message and of the last stamp: counter back to 0
	check("physical ahead", NewHLC(at(2000)).Receive(HLCTime{1000 * ms, 3}), HLCTime{2000 * ms, 0})
	// the message is ahead of the physical clock: take its time, one counter step after it
	check("message ahead", NewHLC(at(1000)).Receive(HLCTime{1500 * ms, 3}), HLCTime{1500 * ms, 4})
	// the physical clock equals the message's time
	check("clock equals message", NewHLC(at(1500)).Receive(HLCTime{1500 * ms, 2}), HLCTime{1500 * ms, 3})
	// the last stamp is as far ahead as the clock allows and the message is behind
	h := NewHLC(at(1000))
	h.Now()
	h.Now() // {1000, 1}
	check("last stamp ahead", h.Receive(HLCTime{500 * ms, 9}), HLCTime{1000 * ms, 2})
	// the last stamp and the message have the same physical part: the larger counter plus one
	g := NewHLC(at(1000))
	g.Receive(HLCTime{1500 * ms, 2}) // {1500, 3}
	check("same physical part", g.Receive(HLCTime{1500 * ms, 7}), HLCTime{1500 * ms, 8})
	check("same physical part, smaller counter", g.Receive(HLCTime{1500 * ms, 1}), HLCTime{1500 * ms, 9})
}
