#!/usr/bin/env bash
# Usage: test_design.sh [code-root]   (default: code)
# Runs every design code unit under the root:
#   1. Go module (code/go.mod): gofmt check, go vet, go test -race on every package (HLD labs, shared packages)
#   2. Go claim/calc units: folders with main.go and expected.txt; `go run` output must equal expected.txt
#   3. C++ solution units: unit.yaml with "kind: solution"; `bash test.sh <dir>` must pass
#   4. Pattern units: unit.yaml with "kind: pattern"; change_cost.sh output must equal measured-<variant>.tsv
set -euo pipefail
ROOT="$(cd "${1:-code}" && pwd)"
HERE="$(cd "$(dirname "$0")" && pwd)"
fail=0

if [ -f "$ROOT/go.mod" ]; then
  unformatted="$(cd "$ROOT" && gofmt -l .)"
  [ -z "$unformatted" ] || { echo "FAIL (gofmt): $unformatted"; fail=1; }
  log="$(mktemp)"
  if ! (cd "$ROOT" && go vet ./... && go test -race -count=1 ./...) > "$log" 2>&1; then
    echo "FAIL (go vet / go test):"; grep -E -- '^(--- FAIL|FAIL|panic|WARNING: DATA RACE)|\.go:[0-9]+' "$log" | head -40; fail=1
  fi
  rm -f "$log"
  while IFS= read -r m; do
    d="$(dirname "$m")"
    [ -f "$d/expected.txt" ] || continue
    if ! (cd "$ROOT" && go run "./${d#"$ROOT"/}") | diff -q - "$d/expected.txt" > /dev/null; then
      echo "FAIL (output differs from expected.txt): $d"; fail=1
    fi
  done < <(find "$ROOT" -name main.go | sort)
fi

while IFS= read -r y; do
  d="$(dirname "$y")"
  if grep -q '^kind: solution' "$y"; then
    log="$(mktemp)"
    bash "$d/test.sh" "$d" > "$log" 2>&1 || { echo "FAIL (tests): $d"; tail -20 "$log"; fail=1; }
    rm -f "$log"
  elif grep -q '^kind: pattern' "$y"; then
    variants="$(sed -n 's/^variants: \[\(.*\)\]/\1/p' "$y" | tr -d ' ' | tr ',' ' ')"
    [ -n "$variants" ] || { echo "MISSING variants in $y"; fail=1; continue; }
    for v in $variants; do
      out="$(mktemp)"; err="$(mktemp)"
      if ! bash "$HERE/change_cost.sh" "$d/$v" > "$out" 2> "$err"; then echo "FAIL (change_cost): $d/$v"; cat "$err"; fail=1
      elif ! diff -q "$out" "$d/measured-$v.tsv" > /dev/null; then echo "FAIL (measured-$v.tsv is out of date): $d"; fail=1; fi
      rm -f "$out" "$err"
    done
  fi
done < <(find "$ROOT" -name unit.yaml | sort)

[ "$fail" -eq 0 ] && echo "All design code units passed" || exit 1
