#!/usr/bin/env bash
# Usage: exercise_kit_check.sh [exercises-root] [reference-root] [mutants-root]
# A kit is any folder under <exercises-root> that contains test.sh. Its path relative to the root is <rel>
# (for example L2.1/ex-3, or L2.1/ladder/rung-2 for one rung of a change ladder).
#   <exercises-root>/<rel>/test.sh       run as: bash test.sh <absolute-solution-dir>; exit 0 = all tests pass
#   <exercises-root>/<rel>/starter/      compiling stubs (for rung k > 1: the reference of rung k-1)
#   <exercises-root>/<rel>/min_mutants   optional; a number (default 3)
#   <reference-root>/<rel>/              the reference solution
#   <mutants-root>/<rel>/<name>/         deliberately wrong solutions
#   <exercises-root>/<rel>/needs_docker  optional marker: the kit's tests start containers. Such kits are
#                                        skipped (and reported) when Docker is unavailable, unless REQUIRE_DOCKER=1.
# Checks: tests FAIL on the starter, PASS on the reference, and FAIL on every mutant; enough mutants exist.
set -euo pipefail
EX="$(cd "${1:-exercises}" && pwd)"; REF="$(cd "${2:-reference}" && pwd)"
MUT="${3:-reference-mutants}"; mkdir -p "$MUT"; MUT="$(cd "$MUT" && pwd)"
fail=0
docker_ok=0; docker info > /dev/null 2>&1 && docker_ok=1
while IFS= read -r t; do
  kit="$(dirname "$t")"; rel="${kit#"$EX"/}"
  ref="$REF/$rel"
  if [ -f "$kit/needs_docker" ] && [ "$docker_ok" -eq 0 ]; then
    if [ "${REQUIRE_DOCKER:-0}" = "1" ]; then echo "FAIL: Docker unavailable for $rel"; fail=1; else echo "SKIPPED (Docker unavailable): $rel"; fi
    continue
  fi
  [ -d "$kit/starter" ] || { echo "MISSING starter: $rel"; fail=1; continue; }
  [ -d "$ref" ] || { echo "MISSING reference: $rel"; fail=1; continue; }
  if bash "$t" "$kit/starter" > /dev/null 2>&1; then echo "FAIL: tests pass on the starter: $rel"; fail=1; fi
  bash "$t" "$ref" > /dev/null 2>&1 || { echo "FAIL: reference does not pass: $rel"; fail=1; }
  min=3; [ -f "$kit/min_mutants" ] && min="$(tr -dc '0-9' < "$kit/min_mutants")"
  count=0
  for m in "$MUT/$rel"/*/; do
    [ -d "$m" ] || continue
    count=$((count+1))
    if bash "$t" "${m%/}" > /dev/null 2>&1; then echo "FAIL: tests pass on mutant $rel/$(basename "$m") (tests too weak)"; fail=1; fi
  done
  [ "$count" -ge "$min" ] || { echo "FAIL: $count mutants for $rel, need $min"; fail=1; }
done < <(find "$EX" -name test.sh | sort)
[ "$fail" -eq 0 ] && echo "All exercise kits consistent" || exit 1
