#!/usr/bin/env bash
# Applies each deliberately wrong change of the H4.2 mistake catalogue to a temporary copy of the lab and prints which test fails.
# usage: bash run.sh [name ...]   (default: all)  Output of this script is what the lesson quotes.
set -uo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"
exec python3 - "$ROOT" "$@" <<'PY'
import os, shutil, subprocess, sys
root = sys.argv[1]
lab = os.path.join(root, "code/H4.2/lab-quorumkv")
# name: (file, text to replace, wrong text, extra go test flags)
M = {
 "m1_no_lock": ("quorumkv.go", "\tr.mu.Lock()\n\tdefer r.mu.Unlock()\n\tswitch m := req.(type)", "\tswitch m := req.(type)", ["-race"]),
 "m2_first_reply": ("quorumkv.go", "if v := r.resp.(Versioned); v.Version > best.Version {\n\t\t\tbest = v\n\t\t}", "if best.Version == 0 {\n\t\t\tbest = r.resp.(Versioned)\n\t\t}", []),
 "m3_overwrite_with_older": ("quorumkv.go", "if m.V.Version > r.data[m.Key].Version { // keep only newer versions\n\t\t\tr.data[m.Key] = m.V\n\t\t}", "r.data[m.Key] = m.V", []),
 "m4_count_attempts": ("quorumkv.go", "acks := len(c.fanOut(c.Replicas, PutReq{key, v}))", "c.fanOut(c.Replicas, PutReq{key, v})\n\tacks := len(c.Replicas)", []),
 "m5_no_timeout": ("httpx.go", "ctx, cancel := context.WithTimeout(context.Background(), h.Timeout)", "ctx, cancel := context.WithCancel(context.Background())", ["-run", "TestBlackholed", "-timeout", "5s"]),
}
for n in (sys.argv[2:] or list(M)):
    fname, old, new, flags = M[n]
    d = os.path.join(root, "code/H4.2/tmpmut-" + n)
    shutil.rmtree(d, ignore_errors=True)
    shutil.copytree(lab, d, ignore=shutil.ignore_patterns("cmd", "experiments"))
    s = open(os.path.join(d, fname)).read()
    print("=== " + n)
    if old not in s:
        print("[pattern not found; update run.sh]"); shutil.rmtree(d); continue
    open(os.path.join(d, fname), "w").write(s.replace(old, new, 1))
    args = ["go", "test", "-count=1"] + (["-timeout", "20s"] if "-timeout" not in flags else []) + (["-race"] if "-race" in flags else []) + [f for f in flags if f != "-race"] + ["./H4.2/tmpmut-" + n]
    p = subprocess.run(args, cwd=os.path.join(root, "code"), capture_output=True, text=True)
    out = (p.stdout + p.stderr).strip().splitlines()
    print("\n".join(out[:int(os.environ.get("LINES_MAX", "12"))])); print(f"[exit {p.returncode}]")
    shutil.rmtree(d, ignore_errors=True)
PY
