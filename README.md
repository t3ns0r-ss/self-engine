# CP Training

A self-study competitive programming site (Astro + Starlight + React). The full plan is in `PLAN.md`. The problem bank plan is in `PROBLEM_BANK_PLAN.md`. Current status is in `PROGRESS.md`. Feedback goes in `FEEDBACK.md`. Agents and new contributors: start with `DEVELOPER_GUIDE.md`.

## Run locally
```
npm install
npm run dev                         # live editing at http://localhost:4321
npm run build && npm run preview    # check the production build
```
`npm run build` first validates all data (`npm run validate`) and checks that `problem-bank/` is up to date. Then it builds the static site into `dist/`.

## Tests
| Command | What it checks |
|---|---|
| `bash scripts/test_units.sh code` | every lesson code unit: compiles with `-Wall -Wextra -Werror`, passes its fixed tests, and passes 5000 random cases against its brute force. Run it locally (for example `code/1.6`); CI does not run it |
| `bash scripts/stress.sh code/1.3/window-sum 2000` | one unit against its brute force |
| `npm test` | the data validators |
| `npm run test:e2e` | every component and page in a real browser, on a temporary placeholder topic (needs Playwright: `npm install --no-save playwright && npx playwright install chromium`) |

GitHub Actions runs all four on every push and pull request (`.github/workflows/ci.yml`).

## Where things live
| Path | What |
|---|---|
| `src/data/curriculum.yaml` | the 48 topics, in order |
| `src/data/bank/patterns/{id}.yaml` | the patterns for each topic (a pattern is a named sub-type of the topic's technique, with the precondition that makes it work) |
| `src/data/bank/{id}.yaml` | the problems for each topic: practice and reserved sets |
| `notes/bank/{id}.md` | solution notes for every bank problem (not shown on the site) |
| `problem-bank/` | readable lists generated from the bank; regenerate with `npm run bank:md`, never edit by hand |
| `src/data/topics/{id}.yaml` | each lesson's cards, ladder, drill, checkpoint, reviews, decision map (problems referenced by bank id) |
| `src/data/glossary.yaml` | glossary terms |
| `src/content/docs/` | lessons (MDX), the method page, phase intros and exams |
| `code/{topic}/` | tested lesson code units |
| `src/lib/` | schemas, validation, data loading, browser storage |
| `src/components/`, `src/pages/` | lesson components and generated pages |
| `tests/placeholder/` | the placeholder topic used only by tests; it is never committed into `src/` |

## Publish on GitHub Pages (current setup)
The site is static, so GitHub Pages hosts it for free at **https://t3ns0r-ss.github.io/self-engine/**.

- **One-time setup:** on GitHub, open the repository's **Settings → Pages**, and under **Build and deployment → Source** choose **GitHub Actions**.
- After that, every push to the default branch runs `.github/workflows/pages.yml`. It runs the code tests and the build (with the `/self-engine/` base path), checks every internal link, and publishes `dist/`. A failed check publishes nothing, so the live site stays as it was.
- To publish without pushing: **Actions → Pages → Run workflow**.
- Internal links in components must go through `url()` from `src/lib/url.ts`, and links in MDX must be relative, so they work under `/self-engine/`. `npm run check:links` (after a build with `BASE_PATH=/self-engine/`) catches any that don't.

## Alternative: your own server
`scripts/deploy.sh`, `.env.deploy.example`, and the Caddy and nginx examples in `deploy/` publish the same `dist/` to a server over SSH with `rsync`. Copy `.env.deploy.example` to `.env.deploy`, fill in `DEPLOY_HOST`, `DEPLOY_PATH`, and `SITE_URL`, then run `bash scripts/deploy.sh`; it uploads only if the code tests and the build pass. HTTPS is required, because the "Copy feedback" button uses the browser clipboard. An optional CI job deploys to the server on pushes to `main` when the repository variable `DEPLOY_ENABLED` is `true` and the secrets `DEPLOY_SSH_KEY`, `DEPLOY_HOST`, `DEPLOY_PATH`, and `SITE_URL` are set.

## Linking your profiles (Codeforces, AtCoder, LeetCode)

Open **Profiles** in the sidebar and enter your handles. From then on every problem on the site (ladders, the problems
table, the dashboard, checkpoints, reviews, the re-solve list) shows its status from your real submissions, next to a
small platform mark. Your own log (minutes, hints, mistakes) is never overwritten: synced statuses are worked out when
a page loads and are never stored in it, and a status you set by hand always wins. Removing a handle removes only its
cached submissions.

- **Codeforces**: type your handle, press *Save and sync*. Requests go from your browser to the Codeforces API (direct,
  or through JSONP if the browser blocks the direct call). One request per 2.1 seconds.
- **AtCoder**: type your user id. Submissions come from AtCoder Problems (an unofficial service) at one request per 1.1 s.
- **LeetCode**: LeetCode has no public API for your history, so statuses arrive from a snippet that you run yourself on
  leetcode.com. Steps (desktop browser with developer tools only):
  1. On the Profiles page enter your username and press *Copy LeetCode snippet*.
  2. Open leetcode.com in the same browser, logged in, and open the developer tools console (F12, then Console).
  3. Paste and press Enter. It makes at most one request per second and never reads your session cookie.
  4. When it finishes it prints a link ending in `#lc=...` and copies the result. Open the link, or paste the result into
     *Import a submissions file* on the Profiles page.
  The snippet is generated from `src/lib/sync/snippet.ts` (written from the output of the read-only probe
  `docs/sync/leetcode-probe.js`). It pages through your solved and attempted lists, 50 problems per request.
- **Import a file**: if no automatic route works, save the API response from the address bar and import it.

Sync runs when the site opens (if the last sync is older than 15 minutes) and when you return to the tab after opening a
problem. The dashboard shows when it last ran and lists solved problems that still need a log entry. A reserved problem
(drill, look-alike, checkpoint, review, exam) that you had already solved before the site showed it is flagged and does
not count toward pass rules.

Developer notes: the code is in `src/lib/sync/`, notes on the platform APIs in `docs/sync/API_NOTES.md`, the build checks
in `scripts/check_sync.mjs`. After adding Codeforces problems to the site, run `node scripts/cf_aliases.mjs` (hand-run,
slow, large downloads cached in `.cache/cf/`) so problems that appear in two parallel rounds match.

### Optional same-origin proxy (your own server only)

GitHub Pages cannot proxy, but the sync works there without it. On your own server you can forward exactly three GET
paths so the browser sees them as same-origin: build with `SYNC_PROXY_BASE=/sync-proxy npm run build` and use the
`/sync-proxy/` blocks in `deploy/Caddyfile.example` or `deploy/nginx.conf.example` (both validated, see
`docs/sync/API_NOTES.md`). If your server sends a `Content-Security-Policy`, allow `script-src https://codeforces.com`
(for the JSONP route) and `connect-src https://codeforces.com https://kenkoooo.com`.

## Your progress is tied to the site's address
Progress lives in your browser and belongs to one exact address (protocol + domain + port). If you move the site to a new domain, or switch between `http` and `https`, it starts empty. Before changing the address, export your progress on the site's Progress page (`/progress/`), then import it on the new address. Use the same export and import to move between phone and laptop.
