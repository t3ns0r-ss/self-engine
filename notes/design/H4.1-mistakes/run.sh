#!/usr/bin/env bash
# Applies each deliberately wrong change of the H4.1 mistake catalogue to a temporary copy of the lab and prints which test fails.
# usage: bash run.sh [name ...]   (default: all)  Output of this script is what the lesson quotes.
set -uo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"
exec python3 - "$ROOT" "$@" <<'PY'
import os, shutil, subprocess, sys
root = sys.argv[1]
lab = os.path.join(root, "code/H4.1/lab-clocks")
# name: (file, text to replace, wrong text, extra go test flags)
M = {
 "m1_receive_without_max": ("clocks.go", "\tif remote > l.t {\n\t\tl.t = remote\n\t}\n\tl.t++", "\tl.t++", []),
 "m2_receive_replaces_own_clock": ("clocks.go", "Merge(p.vc, m.V).Inc(p.ID)", "m.V.Inc(p.ID)", []),
 "m3_compare_by_sum": ("clocks.go", "func Compare(a, b VC) Order {", "func Compare(a, b VC) Order {\n\tsa, sb := uint64(0), uint64(0)\n\tfor _, n := range a {\n\t\tsa += n\n\t}\n\tfor _, n := range b {\n\t\tsb += n\n\t}\n\tif sa != sb {\n\t\tif sa < sb {\n\t\t\treturn Before\n\t\t}\n\t\treturn After\n\t}\n\treturn compareEntries(a, b)\n}\n\nfunc compareEntries(a, b VC) Order {", []),
 "m4_no_lock_in_process": ("clocks.go", "func (p *Process) Local(label string) Stamp {\n\tp.mu.Lock()\n\tdefer p.mu.Unlock()", "func (p *Process) Local(label string) Stamp {", ["-race", "-run", "TestConcurrentUse"]),
 "m6_hlc_without_counter": ("clocks.go", "\t} else {\n\t\th.last.C++\n\t}\n\treturn h.last", "\t}\n\treturn h.last", []),
 "m7_hlc_ignores_message_time": ("clocks.go", "l := max(h.last.L, m.L, pt)", "l := max(h.last.L, pt)", []),
}
names = sys.argv[2:] or list(M) + ["m5_wall_clock"]
for n in names:
    if n == "m5_wall_clock":   # a design mistake: the unchanged lab already shows it
        print("=== m5_wall_clock (no patch: the wall-clock register is the mistake)")
        args = ["go", "test", "-count=1", "-v", "-run", "TestWallClockInvertsCausalOrder", "./H4.1/lab-clocks"]
        p = subprocess.run(args, cwd=os.path.join(root, "code"), capture_output=True, text=True)
        print("\n".join((p.stdout + p.stderr).strip().splitlines()[:6])); print(f"[exit {p.returncode}]")
        continue
    fname, old, new, flags = M[n]
    d = os.path.join(root, "code/H4.1/tmpmut-" + n)
    shutil.rmtree(d, ignore_errors=True)
    shutil.copytree(lab, d, ignore=shutil.ignore_patterns("cmd"))
    s = open(os.path.join(d, fname)).read()
    print("=== " + n)
    if old not in s:
        print("[pattern not found; update run.sh]"); shutil.rmtree(d); continue
    open(os.path.join(d, fname), "w").write(s.replace(old, new, 1))
    args = ["go", "test", "-count=1", "-timeout", "60s"] + flags + ["./H4.1/tmpmut-" + n]
    p = subprocess.run(args, cwd=os.path.join(root, "code"), capture_output=True, text=True)
    out = (p.stdout + p.stderr).strip().splitlines()
    print("\n".join(out[:int(os.environ.get("LINES_MAX", "9"))])); print(f"[exit {p.returncode}]")
    shutil.rmtree(d, ignore_errors=True)
PY
