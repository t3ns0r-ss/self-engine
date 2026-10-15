#!/usr/bin/env bash
# Usage: test_design.sh [code-root]   (default: code)
# Runs every design code unit under the root:
#   1. claim/calc units: check.py or calc.py; stdout must equal expected.txt exactly
#   2. pattern units (unit.yaml with "kind: pattern"): change_cost.sh stdout must equal measured-<variant>.tsv
#   3. C# solutions (*.sln): dotnet test   (edit this block if lld_language changes; see Section 3)
set -euo pipefail
ROOT="${1:-code}"
HERE="$(cd "$(dirname "$0")" && pwd)"
fail=0

while IFS= read -r f; do
  d="$(dirname "$f")"
  if [ ! -f "$d/expected.txt" ]; then echo "MISSING expected.txt: $d"; fail=1; continue; fi
  if ! python3 -I "$f" | diff -q - "$d/expected.txt" > /dev/null; then echo "FAIL (output differs from expected.txt): $d"; fail=1; fi
done < <(find "$ROOT" \( -name check.py -o -name calc.py \) | sort)

while IFS= read -r y; do
  d="$(dirname "$y")"
  grep -q '^kind: pattern' "$y" || continue
  variants="$(sed -n 's/^variants: \[\(.*\)\]/\1/p' "$y" | tr -d ' ' | tr ',' ' ')"
  [ -n "$variants" ] || { echo "MISSING variants in $y"; fail=1; continue; }
  for v in $variants; do
    out="$(mktemp)"; err="$(mktemp)"
    if ! bash "$HERE/change_cost.sh" "$d/$v" > "$out" 2> "$err"; then echo "FAIL (change_cost): $d/$v"; cat "$err"; fail=1
    elif ! diff -q "$out" "$d/measured-$v.tsv" > /dev/null; then echo "FAIL (measured-$v.tsv is out of date): $d"; fail=1; fi
    rm -f "$out" "$err"
  done
done < <(find "$ROOT" -name unit.yaml | sort)

while IFS= read -r sln; do
  command -v dotnet > /dev/null || { echo "dotnet not installed; cannot test $sln"; fail=1; continue; }
  dotnet test "$sln" --nologo -warnaserror > /dev/null || { echo "FAIL (dotnet test): $sln"; fail=1; }
done < <(find "$ROOT" -name '*.sln' | sort)

[ "$fail" -eq 0 ] && echo "All design code units passed" || exit 1
