#!/usr/bin/env bash
# Browser test of every component on a temporary placeholder topic (PLAN.md M0).
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
node tests/placeholder/make.mjs
node scripts/validate.mjs
node scripts/bank_md.mjs > /dev/null
npx astro build > /dev/null
node scripts/check_links.mjs
npx astro preview --port 4329 > /dev/null 2>&1 &
PREVIEW_PID=$!
for _ in $(seq 1 30); do curl -sf http://localhost:4329/self-engine/ > /dev/null && break; sleep 0.5; done
BASE=http://localhost:4329/self-engine node tests/e2e/lesson.cjs
for f in tests/e2e/pages.cjs; do [ -f "$f" ] && BASE=http://localhost:4329/self-engine node "$f"; done
