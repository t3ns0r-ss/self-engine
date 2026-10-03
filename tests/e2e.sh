#!/usr/bin/env bash
# Browser tests: every real lesson (tests/e2e/lessons.cjs), then every component on a temporary
# placeholder topic (PLAN.md M0).
# Needs Playwright with Chromium: set PLAYWRIGHT_PATH to the playwright package if it is not
# installed in this project, and CHROMIUM to a browser binary if Playwright has none downloaded.
set -euo pipefail
cd "$(dirname "$0")/.."
# Build under the same base path as GitHub Pages, so every link is tested with it.
export BASE_PATH=/self-engine/
cleanup() {
  [ -n "${PREVIEW_PID:-}" ] && kill "$PREVIEW_PID" 2>/dev/null || true
  node tests/placeholder/make.mjs --remove
  node scripts/bank_md.mjs > /dev/null
}
trap cleanup EXIT
# The preview server runs as our own child (no npx wrapper, so kill reaches it); --ignore-lock lets
# it start even if another preview server holds the lock.
wait_up() {
  for _ in $(seq 1 60); do curl -sf http://localhost:4329/self-engine/ > /dev/null && return 0; sleep 0.5; done
  echo "preview server did not start"; return 1
}
# 1. The real lessons, built without the placeholder (it replaces topic 1.3's files while it exists).
node scripts/validate.mjs
npx astro build > /dev/null
./node_modules/.bin/astro preview --port 4329 --ignore-lock > /dev/null 2>&1 &
PREVIEW_PID=$!
wait_up
BASE=http://localhost:4329/self-engine node tests/e2e/lessons.cjs
kill "$PREVIEW_PID"; wait "$PREVIEW_PID" 2>/dev/null || true
PREVIEW_PID=
# 2. Every component on the placeholder topic.
node tests/placeholder/make.mjs
node scripts/validate.mjs
node scripts/bank_md.mjs > /dev/null
npx astro build > /dev/null
node scripts/check_links.mjs
./node_modules/.bin/astro preview --port 4329 --ignore-lock > /dev/null 2>&1 &
PREVIEW_PID=$!
wait_up
BASE=http://localhost:4329/self-engine node tests/e2e/lesson.cjs
for f in tests/e2e/pages.cjs; do [ -f "$f" ] && BASE=http://localhost:4329/self-engine node "$f"; done
