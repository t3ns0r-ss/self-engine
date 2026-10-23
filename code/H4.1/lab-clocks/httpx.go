package clocks

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"net/http"
	"strings"
	"time"
)

// HTTPSender is a Sender that posts messages to the other processes' /recv endpoint.
// URLs maps a process id to its base URL. Every call has a timeout, so a dead peer costs one timeout.
type HTTPSender struct {
	URLs    map[string]string
	Timeout time.Duration
}

type wireMsg struct {
	From    string
	Payload string
	L       uint64
	V       VC
}

func (h *HTTPSender) Send(from, to string, msg any) {
	m, ok := msg.(Msg)
	base, known := h.URLs[to]
	if !ok || !known {
		return
	}
	body, _ := json.Marshal(wireMsg{from, m.Payload, m.L, m.V})
	ctx, cancel := context.WithTimeout(context.Background(), h.Timeout)
	defer cancel()
	req, _ := http.NewRequestWithContext(ctx, http.MethodPost, base+"/recv", bytes.NewReader(body))
	if resp, err := http.DefaultClient.Do(req); err == nil {
		resp.Body.Close()
	}
}

// HTTPHandler exposes a Process: POST /local?label=x, POST /send?to=B&payload=x, POST /recv, GET /log.
func HTTPHandler(p *Process) http.Handler {
	mux := http.NewServeMux()
	reply := func(w http.ResponseWriter, s Stamp) {
		json.NewEncoder(w).Encode(map[string]any{"proc": s.Proc, "event": s.Label, "lamport": s.L, "vector": s.V.String()})
	}
	mux.HandleFunc("POST /local", func(w http.ResponseWriter, r *http.Request) { reply(w, p.Local(r.URL.Query().Get("label"))) })
	mux.HandleFunc("POST /send", func(w http.ResponseWriter, r *http.Request) {
		reply(w, p.SendTo(r.URL.Query().Get("to"), r.URL.Query().Get("payload")))
	})
	mux.HandleFunc("POST /recv", func(w http.ResponseWriter, r *http.Request) {
		var m wireMsg
		if err := json.NewDecoder(r.Body).Decode(&m); err != nil {
			http.Error(w, err.Error(), http.StatusBadRequest)
			return
		}
		p.Handle(m.From, Msg{Payload: m.Payload, L: m.L, V: m.V})
		w.WriteHeader(http.StatusNoContent)
	})
	mux.HandleFunc("GET /log", func(w http.ResponseWriter, r *http.Request) {
		var lines []string
		for _, s := range p.Log() {
			lines = append(lines, fmt.Sprintf("%s L=%d V=%s", s.Label, s.L, s.V))
		}
		fmt.Fprintln(w, strings.Join(lines, "\n"))
	})
	return mux
}
