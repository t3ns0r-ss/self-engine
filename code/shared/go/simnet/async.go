package simnet

import (
	"container/heap"
	"math/rand"
	"sync"
	"time"
)

// Clock is the time source a mechanism reads. In tests it is the AsyncNet's virtual clock, so election
// timeouts and lease expiries run without real waiting. In real processes it is a wrapper over time.Now.
type Clock interface {
	Now() time.Time
}

// SystemClock is the Clock for real processes.
type SystemClock struct{}

func (SystemClock) Now() time.Time { return time.Now() }

// AsyncNet is the asynchronous mode of simnet: Send puts a message in a queue ordered by a virtual
// clock; delays come from a seeded random source; the test moves time forward with Step and RunUntilIdle.
// Two runs with the same seed and the same calls deliver messages in the same order.
// All methods are safe for concurrent use, but handlers run on the goroutine that calls Step.
type AsyncNet struct {
	mu       sync.Mutex
	rng      *rand.Rand
	now      time.Time
	seq      uint64
	queue    eventQueue
	handlers map[string]func(from string, msg any)
	down     map[string]bool
	cut      map[[2]string]bool
	minDelay time.Duration
	maxDelay time.Duration
	log      []Delivery
}

// Delivery records one delivered message, for tests that compare message orders between runs.
type Delivery struct {
	At       time.Duration // virtual time since the start
	From, To string
	Msg      any
}

type event struct {
	at  time.Time
	seq uint64 // tie-break: events at the same virtual time run in the order they were queued
	run func()
	msg *Delivery
}

type eventQueue []*event

func (q eventQueue) Len() int { return len(q) }
func (q eventQueue) Less(i, j int) bool {
	if q[i].at.Equal(q[j].at) {
		return q[i].seq < q[j].seq
	}
	return q[i].at.Before(q[j].at)
}
func (q eventQueue) Swap(i, j int) { q[i], q[j] = q[j], q[i] }
func (q *eventQueue) Push(x any)   { *q = append(*q, x.(*event)) }
func (q *eventQueue) Pop() any {
	old := *q
	e := old[len(old)-1]
	*q = old[:len(old)-1]
	return e
}

// NewAsync creates an asynchronous network. The virtual clock starts at the Unix epoch.
// The default delay is a fixed 1 ms; use SetDelay for a random range.
func NewAsync(seed int64) *AsyncNet {
	return &AsyncNet{
		rng:      rand.New(rand.NewSource(seed)),
		now:      time.Unix(0, 0),
		handlers: map[string]func(string, any){},
		down:     map[string]bool{},
		cut:      map[[2]string]bool{},
		minDelay: time.Millisecond,
		maxDelay: time.Millisecond,
	}
}

// Now returns the virtual time. AsyncNet implements Clock.
func (n *AsyncNet) Now() time.Time {
	n.mu.Lock()
	defer n.mu.Unlock()
	return n.now
}

// Register installs the handler for node id.
func (n *AsyncNet) Register(id string, h func(from string, msg any)) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.handlers[id] = h
}

// SetDelay sets the range from which each message's delay is drawn (uniformly, from the seeded source).
func (n *AsyncNet) SetDelay(min, max time.Duration) {
	n.mu.Lock()
	defer n.mu.Unlock()
	if max < min {
		max = min
	}
	n.minDelay, n.maxDelay = min, max
}

func (n *AsyncNet) SetDown(id string, down bool) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.down[id] = down
}

func (n *AsyncNet) Partition(a, b string, cut bool) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.cut[[2]string{a, b}] = cut
	n.cut[[2]string{b, a}] = cut
}

// Send queues msg for delivery after a random delay. A message is dropped, silently, if at delivery time
// the destination is down, the sender is down, or the link is cut. Messages queued earlier can be
// delivered later than messages queued after them when their delays differ (reordering).
func (n *AsyncNet) Send(from, to string, msg any) {
	n.mu.Lock()
	defer n.mu.Unlock()
	d := n.minDelay
	if n.maxDelay > n.minDelay {
		d += time.Duration(n.rng.Int63n(int64(n.maxDelay-n.minDelay) + 1))
	}
	n.seq++
	heap.Push(&n.queue, &event{at: n.now.Add(d), seq: n.seq, msg: &Delivery{From: from, To: to, Msg: msg}})
}

// AfterFunc runs f once the virtual clock has advanced by d (timers for election timeouts, leases).
func (n *AsyncNet) AfterFunc(d time.Duration, f func()) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.seq++
	heap.Push(&n.queue, &event{at: n.now.Add(d), seq: n.seq, run: f})
}

// Step runs the earliest queued event (a message delivery or a timer) and advances the clock to its time.
// It reports whether there was an event.
func (n *AsyncNet) Step() bool {
	n.mu.Lock()
	if n.queue.Len() == 0 {
		n.mu.Unlock()
		return false
	}
	e := heap.Pop(&n.queue).(*event)
	if e.at.After(n.now) {
		n.now = e.at
	}
	var h func(string, any)
	if e.msg != nil {
		m := e.msg
		blocked := n.down[m.To] || n.down[m.From] || n.cut[[2]string{m.From, m.To}]
		h = n.handlers[m.To]
		if blocked || h == nil {
			h = nil
		} else {
			m.At = n.now.Sub(time.Unix(0, 0))
			n.log = append(n.log, *m)
		}
	}
	n.mu.Unlock() // never hold the lock while user code runs
	if e.run != nil {
		e.run()
	} else if h != nil {
		h(e.msg.From, e.msg.Msg)
	}
	return true
}

// RunUntilIdle steps until no event is queued, or until limit events have run (a guard against
// mechanisms that keep sending forever). It returns the number of events run.
func (n *AsyncNet) RunUntilIdle(limit int) int {
	c := 0
	for c < limit && n.Step() {
		c++
	}
	return c
}

// RunFor advances virtual time by d, running every event due within it, then sets the clock to now+d.
func (n *AsyncNet) RunFor(d time.Duration) {
	n.mu.Lock()
	end := n.now.Add(d)
	n.mu.Unlock()
	for {
		n.mu.Lock()
		due := n.queue.Len() > 0 && !n.queue[0].at.After(end)
		n.mu.Unlock()
		if !due {
			break
		}
		n.Step()
	}
	n.mu.Lock()
	n.now = end
	n.mu.Unlock()
}

// Log returns the deliveries so far, in delivery order.
func (n *AsyncNet) Log() []Delivery {
	n.mu.Lock()
	defer n.mu.Unlock()
	return append([]Delivery(nil), n.log...)
}
