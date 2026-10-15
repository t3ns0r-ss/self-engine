#!/usr/bin/env bash
# Usage: change_cost.sh <variant-dir>
# <variant-dir> contains: base/ (starting code), scenarios/NN-name.patch (applied cumulatively, in name order),
# and test.sh (called as: bash test.sh <work-dir>; must exit 0 on the base and after every scenario).
# Prints only the measurement table on stdout; test output is discarded (it is shown only on failure).
set -euo pipefail
V="${1:?usage: change_cost.sh <variant-dir>}"
V="$(cd "$V" && pwd)"
W="$(mktemp -d)"
LOG="$(mktemp)"
trap 'rm -rf "$W" "$LOG"' EXIT
cp -r "$V/base/." "$W/"
cd "$W"
git init -q .
git config user.email "t@example.com"; git config user.name "t"
git add -A; git commit -qm base
run_tests() {
  if ! bash "$V/test.sh" "$W" > "$LOG" 2>&1; then
    echo "FAIL: tests fail $1" >&2; cat "$LOG" >&2; exit 1
  fi
}
run_tests "on base"
files=$(git ls-files | wc -l)
loc=$(git ls-files -z | xargs -0 awk 'NF { c++ } END { print c + 0 }')
printf "base\tfiles=%s\tnonblank_lines=%s\n" "$files" "$loc"
printf "scenario\tfiles_modified\tfiles_added\tfiles_deleted\tlines_added_in_modified\tlines_removed_in_modified\tlines_in_new_files\n"
for p in "$V"/scenarios/*.patch; do
  git apply --index "$p"
  mod=0; add=0; del=0; la=0; lr=0; ln=0
  while IFS=$'\t' read -r a r path; do
    [ "$a" = "-" ] && { echo "FAIL: binary file in scenario $(basename "$p"): $path" >&2; exit 1; }
    status=$(git diff --cached --no-renames --name-status -- "$path" | cut -f1)
    case "$status" in
      A) add=$((add+1)); ln=$((ln+a)) ;;
      D) del=$((del+1)) ;;
      *) mod=$((mod+1)); la=$((la+a)); lr=$((lr+r)) ;;
    esac
  done < <(git diff --cached --no-renames --numstat)
  git commit -qm "$(basename "$p")"
  run_tests "after $(basename "$p")"
  printf "%s\t%s\t%s\t%s\t%s\t%s\t%s\n" "$(basename "$p" .patch)" "$mod" "$add" "$del" "$la" "$lr" "$ln"
done
