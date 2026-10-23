// Package execs lists every small execution of a message-passing system, so claim programs can check
// a statement about clocks on all of them. An execution is a sequence of events: a local event at one
// process, a send from one process to another, or the receipt of a message that is still in transit.
// Messages may be received in any order. Stamps are computed with the lab's real clock code.
package execs

import clocks "selfengine/code/H4.1/lab-clocks"

type Kind int

const (
	Local Kind = iota
	Send
	Recv
)

type Event struct {
	Proc int
	Kind Kind
	Msg  int // message id for Send and Recv
	L    uint64
	V    clocks.VC
}

type Execution struct {
	Events []Event
	// Before[i][j] is true when event i happened before event j: the transitive closure of
	// "earlier at the same process" and "send before its receive".
	Before [][]bool
}

type msg struct {
	to int
	l  uint64
	v  clocks.VC
	id int
}

type state struct {
	n       int
	lam     []*clocks.Lamport
	vc      []clocks.VC
	pending []msg
	events  []Event
	sendIdx map[int]int // message id -> index of its send event
	nextID  int
}

// Enumerate calls visit for every execution of nProcs processes with 1 to maxEvents events.
func Enumerate(nProcs, maxEvents int, visit func(*Execution)) {
	s := &state{n: nProcs, lam: make([]*clocks.Lamport, nProcs), vc: make([]clocks.VC, nProcs), sendIdx: map[int]int{}}
	for i := range s.vc {
		s.vc[i] = clocks.VC{}
		s.lam[i] = clocks.LamportAt(0)
	}
	s.walk(maxEvents, visit)
}

func name(p int) string { return string(rune('A' + p)) }

func (s *state) walk(left int, visit func(*Execution)) {
	if len(s.events) > 0 {
		visit(s.execution())
	}
	if left == 0 {
		return
	}
	for p := 0; p < s.n; p++ {
		s.step(left, visit, p, Local, -1)
		for q := 0; q < s.n; q++ {
			if q != p {
				s.step(left, visit, p, Send, q)
			}
		}
		for i := range s.pending {
			if s.pending[i].to == p {
				s.step(left, visit, p, Recv, i)
			}
		}
	}
}

// step applies one event, explores everything after it, and undoes it.
func (s *state) step(left int, visit func(*Execution), p int, k Kind, arg int) {
	savedL := s.lam[p]
	s.lam[p] = clocks.LamportAt(savedL.Time()) // work on a copy so the saved clock stays untouched
	savedV := s.vc[p]
	savedPending := append([]msg(nil), s.pending...)
	savedID := s.nextID
	var e Event
	switch k {
	case Local:
		e = Event{Proc: p, Kind: Local, Msg: -1, L: s.lam[p].Tick()}
		s.vc[p] = s.vc[p].Inc(name(p))
	case Send:
		s.vc[p] = s.vc[p].Inc(name(p))
		e = Event{Proc: p, Kind: Send, Msg: s.nextID, L: s.lam[p].Send()}
		s.pending = append(s.pending, msg{to: arg, l: e.L, v: s.vc[p], id: s.nextID})
		s.sendIdx[s.nextID] = len(s.events)
		s.nextID++
	case Recv:
		m := s.pending[arg]
		s.pending = append(s.pending[:arg:arg], s.pending[arg+1:]...)
		s.vc[p] = clocks.Merge(s.vc[p], m.v).Inc(name(p))
		e = Event{Proc: p, Kind: Recv, Msg: m.id, L: s.lam[p].Receive(m.l)}
	}
	e.V = s.vc[p]
	s.events = append(s.events, e)
	s.walk(left-1, visit)
	s.events = s.events[:len(s.events)-1]
	s.nextID = savedID
	delete(s.sendIdx, savedID)
	s.pending = savedPending
	s.vc[p] = savedV
	s.lam[p] = savedL
}

func (s *state) execution() *Execution {
	n := len(s.events)
	hb := make([][]bool, n)
	for i := range hb {
		hb[i] = make([]bool, n)
	}
	last := map[int]int{}
	for j, e := range s.events {
		preds := []int{}
		if i, ok := last[e.Proc]; ok {
			preds = append(preds, i)
		}
		if e.Kind == Recv {
			preds = append(preds, s.sendIdx[e.Msg])
		}
		for _, i := range preds {
			hb[i][j] = true
			for x := 0; x < i; x++ {
				if hb[x][i] {
					hb[x][j] = true
				}
			}
		}
		last[e.Proc] = j
	}
	return &Execution{Events: append([]Event(nil), s.events...), Before: hb}
}
