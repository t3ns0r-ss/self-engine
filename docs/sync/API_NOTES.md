# Profile sync: API notes (milestone S0)

Findings from checking `PROFILE_SYNC_PLAN.md` Section 2 against the live services. Dates are when each check was run.
Anything the code relies on is listed here; if a service changes, the service wins and the schemas in
`src/lib/sync/schemas.ts` and the fixtures in `tests/sync/fixtures/` are updated with a dated line below.

## Verified (2026-10-13)

| # | Question | Answer | How it was checked |
|---|---|---|---|
| 1 | Codeforces `user.status` parameters and fields | `handle`, `from` (1-based), `count` work. Each submission has `id`, `creationTimeSeconds`, `verdict`, `problem.{contestId,index,name}`, `author.participantType`. Newest first. | `curl "https://codeforces.com/api/user.status?handle=tourist&from=1&count=3"`; trimmed copy in `tests/sync/fixtures/cf_status.json` |
| 2 | Codeforces `user.info` | Success returns `result[0].handle` in canonical case (`TouRist` -> `tourist`). Unknown handle: HTTP 400 with `{"status":"FAILED","comment":"handles: User with handle ... not found"}`. | `curl`, fixture `cf_bad.json` |
| 3 | Codeforces `contest.list` fields | `id`, `name`, `type`, `phase`, `startTimeSeconds`, `durationSeconds`. | `curl` |
| 4 | Does `problemset.problems` list both copies of a problem used in parallel Div. 1 / Div. 2 rounds? | **No.** A shared problem is listed once, under one contest (for example 1500A "Going Home"; contest 1501 lists only its own A and B). The Div. 2 copy (1501C) exists only in `contest.standings`. So aliases cannot be built from `problemset.problems` alone. | `problemset.problems` filtered by contest 1500 and 1501 |
| 5 | `contest.standings` for aliases | Codeforces only allows the bare form `contest.standings?contestId=<id>` for non-admins (adding `from`/`count` returns an error). The response is large (about 4.6 MB for contest 1501), so `scripts/cf_aliases.mjs` trims it to the problem list before caching and spaces calls 2.1 s apart. It is a hand-run script, never run in the browser. | `curl` with and without `from/count` |
| 6 | Codeforces CORS today | A page on `http://localhost` can read an OK response, and also the HTTP 400 `FAILED` response (both carry `access-control-allow-origin: *`). The 2016 report no longer holds. | Playwright Chromium on the Astro preview server, `fetch` from the page; response headers seen with `curl -D` |
| 7 | Codeforces JSONP | `...&jsonp=cb` returns `cb({...})`. | `curl` |
| 8 | AtCoder Problems submissions | Fields `id`, `epoch_second`, `problem_id`, `contest_id`, `user_id`, `result`, ... . `from_second` is **inclusive** (the first returned submission had `epoch_second == from_second`). Results seen: `AC`, `WA`, `TLE`, `RE`. `problem_id` is the task id (`agc074_a`), which matches the site ids `ac-{task_id}`. | `curl`, fixture `ac.json` |
| 9 | AtCoder user id case | Case-insensitive on AtCoder Problems (`TOURIST` returns tourist's submissions). | `curl` |
| 10 | AtCoder Problems CORS | `access-control-allow-origin: *`; a page on `http://localhost` can read it. | `curl -D`, Playwright |
| 11 | Hosting | The live site is on GitHub Pages (`.github/workflows/pages.yml`), so the same-origin proxy does not exist there; direct fetch and JSONP are the routes. PLAN.md Section 14.2 also describes a self-hosted server, where the proxy can be enabled. | `DEVELOPER_GUIDE.md`, workflows |

## Not verifiable from this environment

- `https://codeforces.com/apiHelp` returns a Cloudflare challenge (HTTP 403) to `curl`, so the documented rate limit
  (1 request per 2 seconds), anonymous access and the verdict list could not be re-read today. The code uses the limit
  from the plan with a margin (2.1 s) and treats unknown verdicts as attempts and logs them, so it does not depend on
  the verdict list. **Re-read the page in a normal browser before the final review.**
- **LeetCode** (item 4 of the plan's list): needs a logged-in browser. The probe is `docs/sync/leetcode-probe.js`; the
  steps are in `PROGRESS.md` under "Questions for Saurabh". The snippet generator is not written until its output is
  known (the plan forbids guessing the query). A public, anonymous request to `https://leetcode.com/graphql` answers
  HTTP 400 "Must provide query string", so the endpoint exists but nothing about its schema was assumed.

## Alias generation result

See the end of this file once `node scripts/cf_aliases.mjs` has finished (appended below).

## Proxy configuration validation (2026-10-13)

`deploy/nginx.conf.example` and `deploy/Caddyfile.example` forward only `GET` of `user.info`, `user.status` and the AtCoder
Problems submissions path; anything else under `/sync-proxy/` is 404.

Commands and results (placeholders filled in temporary copies under `/tmp`; the upstream was replaced by a local stand-in
server that echoes the request it received, because the sandbox cannot reach the real hosts from nginx):

- `nginx -t -c nginx_main_real.conf` with the **unmodified** upstreams (only the domain and root filled in): *syntax is ok, test is successful* (nginx 1.24).
- `caddy validate --config Caddyfile.real --adapter caddyfile` (Caddy 2.8.4), unmodified upstreams: *Valid configuration*.
- Through a running nginx and a running Caddy (stand-in upstream):
  - `GET /sync-proxy/cf/api/user.status?handle=tourist&from=1&count=2` with a `Cookie` header: HTTP 200; the upstream saw no cookie and no authorization header, its `Host` was `codeforces.com`, and its `Set-Cookie` did not reach the client.
  - `GET /sync-proxy/cf/api/user.info?...` and the AtCoder path: HTTP 200 with the right upstream path.
  - `GET /sync-proxy/cf/api/contest.list`: 404. `POST` to an allowed path: 403 (nginx) / 404 (Caddy).
  - The static site is still served at `/`; a missing page is 404.
  - nginx rate limit (`burst=3`, 30 requests/minute for Codeforces): 8 rapid requests gave `200 503 503 503 ...` after earlier requests had used the burst. The client treats 503 as retryable and backs off, and its own gate keeps well below the limit.
- Not tested against the real Codeforces and AtCoder Problems hosts through the proxy (not reachable from nginx here). Do this once on the real server: `curl "https://<site>/sync-proxy/cf/api/user.info?handles=tourist"`.

## Alias generation result (2026-10-13)

`node scripts/cf_aliases.mjs`: 662 Codeforces keys used on the site, 242 contests that ran in parallel with another
contest fetched through `contest.standings` (bare form, trimmed and cached in `.cache/cf/`, about 25 minutes uncached),
112 keys with a twin. Result in `src/data/sync/cf-aliases.json`.

## LeetCode probe result (2026-10-13, run by Saurabh in a logged-in browser)

- `POST /graphql` with the `questionList(categorySlug: "", limit, skip, filters)` query (aliased as `problemsetQuestionList`, fields `totalNum` and `data { titleSlug status }`) works **with and without** the `x-csrftoken` header (HTTP 200 both times). The snippet still sends it when the cookie exists.
- Unfiltered: total 4082 problems, `status` is `"ac"` or `null` on the first page. Filter `{status: "AC"}`: total 91, all `"ac"`. Filter `{status: "TRIED"}`: total 3, all `"notac"`. So the two filters give solved and attempted problems directly, with no list of site problems needed (nothing about reserved problems is revealed).
- The single-problem query `question(titleSlug)` also returns `status` (`"ac"`), but it is not used.
- `copy()` exists in his console (the probe copied its output). Not checked in Firefox.
- The snippet pages at 50 problems per request and one request per second; a limit above 5 was not part of the probe, so the first run of the snippet is the real test of `limit: 50` (gate S4).
