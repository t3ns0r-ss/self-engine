package quorumkv

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"net/http"
	"time"
)

// HTTPHandler exposes a Replica over HTTP: POST /put with {"key","value","version"}, GET /get?key=k.
func HTTPHandler(r *Replica) http.Handler {
	mux := http.NewServeMux()
	mux.HandleFunc("POST /put", func(w http.ResponseWriter, req *http.Request) {
		var m struct {
			Key, Value string
			Version    uint64
		}
		if err := json.NewDecoder(req.Body).Decode(&m); err != nil {
			http.Error(w, err.Error(), http.StatusBadRequest)
			return
		}
		r.Handle("http", PutReq{m.Key, Versioned{m.Value, m.Version}})
		w.WriteHeader(http.StatusNoContent)
	})
	mux.HandleFunc("GET /get", func(w http.ResponseWriter, req *http.Request) {
		v := r.Handle("http", GetReq{req.URL.Query().Get("key")}).(Versioned)
		json.NewEncoder(w).Encode(map[string]any{"value": v.Value, "version": v.Version})
	})
	return mux
}

// HTTPCaller is a Caller that sends requests to nodes by base URL (for example "http://127.0.0.1:7001").
// Every call has a timeout, so a blackholed node counts as down instead of hanging the client.
type HTTPCaller struct {
	URLs    map[string]string
	Timeout time.Duration
	Client  *http.Client
}

func (h *HTTPCaller) Call(_, to string, req any) (any, error) {
	base, ok := h.URLs[to]
	if !ok {
		return nil, fmt.Errorf("quorumkv: unknown node %q", to)
	}
	ctx, cancel := context.WithTimeout(context.Background(), h.Timeout)
	defer cancel()
	cl := h.Client
	if cl == nil {
		cl = http.DefaultClient
	}
	switch m := req.(type) {
	case PutReq:
		body, _ := json.Marshal(map[string]any{"key": m.Key, "value": m.V.Value, "version": m.V.Version})
		hr, _ := http.NewRequestWithContext(ctx, http.MethodPost, base+"/put", bytes.NewReader(body))
		resp, err := cl.Do(hr)
		if err != nil {
			return nil, err
		}
		resp.Body.Close()
		if resp.StatusCode != http.StatusNoContent {
			return nil, fmt.Errorf("quorumkv: %s answered %s", to, resp.Status)
		}
		return true, nil
	case GetReq:
		hr, _ := http.NewRequestWithContext(ctx, http.MethodGet, base+"/get?key="+m.Key, nil)
		resp, err := cl.Do(hr)
		if err != nil {
			return nil, err
		}
		defer resp.Body.Close()
		var out struct {
			Value   string
			Version uint64
		}
		if err := json.NewDecoder(resp.Body).Decode(&out); err != nil {
			return nil, err
		}
		return Versioned{out.Value, out.Version}, nil
	}
	return nil, fmt.Errorf("quorumkv: unsupported request %T", req)
}
