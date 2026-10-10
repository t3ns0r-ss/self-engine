#!/usr/bin/env bash
# Compiles every code unit, checks its fixed tests, and stress-tests units that have brute.cpp and gen.cpp.
# Units run in parallel (JOBS, default: all cores). A unit that passed with identical files is skipped:
# its content hash is kept in $UNIT_STAMPS (default .unit-stamps; CI caches that folder). STRESS_N sets the cases (default 5000).
set -euo pipefail
ROOT="${1:-code}"
export HERE="$(cd "$(dirname "$0")" && pwd)"
export STAMPS="${UNIT_STAMPS:-.unit-stamps}"
export STRESS_N="${STRESS_N:-5000}"
mkdir -p "$STAMPS"

check_unit() {
  unit="$1"
  stamp="$STAMPS/$(echo "$unit" | tr '/' '_').sha"
  hash=$( (find "$unit" -type f -not -path '*/.build/*' | sort | xargs sha256sum; sha256sum "$HERE/stress.sh"; echo "$STRESS_N") | sha256sum | cut -d' ' -f1)
  if [ -f "$stamp" ] && [ "$(cat "$stamp")" = "$hash" ]; then echo "skip (unchanged): $unit"; return 0; fi
  mkdir -p "$unit/.build"
  g++ -std=c++17 -O2 -Wall -Wextra -Werror -o "$unit/.build/solution" "$unit/solution.cpp" || { echo "COMPILE FAIL: $unit"; return 1; }
  for in_file in "$unit"/tests/*.in; do
    [ -e "$in_file" ] || continue
    expected="${in_file%.in}.out"
    actual="$unit/.build/actual.out"
    "$unit/.build/solution" < "$in_file" > "$actual" || { echo "RUN FAIL: $in_file"; return 1; }
    diff -q -Z "$actual" "$expected" > /dev/null || { echo "FAIL: $in_file"; return 1; }
  done
  if [ -f "$unit/brute.cpp" ] && [ -f "$unit/gen.cpp" ]; then
    bash "$HERE/stress.sh" "$unit" "$STRESS_N" > /dev/null || { echo "STRESS FAIL: $unit"; return 1; }
  fi
  echo "$hash" > "$stamp"
}
export -f check_unit

log="$(mktemp)"
if find "$ROOT" -name solution.cpp -exec dirname {} \; | sort | xargs -P "${JOBS:-$(nproc)}" -I{} bash -c 'check_unit "$1"' _ {} > "$log" 2>&1; then
  grep -v '^skip' "$log" || true
  echo "All code units passed"
else
  grep -v '^skip' "$log" || true
  exit 1
fi
