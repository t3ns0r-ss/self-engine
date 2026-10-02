# CP Training

A self-study competitive programming site (Astro + Starlight + React). The full plan is in `PLAN.md`. The problem bank plan is in `PROBLEM_BANK_PLAN.md`. Current status is in `PROGRESS.md`. Feedback goes in `FEEDBACK.md`.

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
| `bash scripts/test_units.sh code` | every lesson code unit: compiles with `-Wall -Wextra -Werror`, passes its fixed tests, and passes 5000 random cases against its brute force |
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

## Deploy to your own server
The site is static, so no Node.js runs on the server.

1. Copy `.env.deploy.example` to `.env.deploy` and fill in `DEPLOY_HOST`, `DEPLOY_PATH`, and `SITE_URL`. The real file is gitignored.
2. Set up the web server with `deploy/Caddyfile.example` (recommended, HTTPS is automatic) or `deploy/nginx.conf.example` (then run `certbot --nginx -d <domain>`). Both include commented-out password protection.
3. Run `bash scripts/deploy.sh`. It runs the code tests and the build, and uploads `dist/` with one `rsync` only if both pass.

HTTPS is required: the "Copy feedback" button uses the browser clipboard, which only works on secure pages.

**Optional deploy on merge to `main`:** in the GitHub repository settings, add the secrets `DEPLOY_SSH_KEY`, `DEPLOY_HOST`, `DEPLOY_PATH`, and `SITE_URL`, then set the repository variable `DEPLOY_ENABLED` to `true`. Use a dedicated server user that can write only to `DEPLOY_PATH`.

## Your progress is tied to the site's address
Progress lives in your browser and belongs to one exact address (protocol + domain + port). If you move the site to a new domain, or switch between `http` and `https`, it starts empty. Before changing the address, export your progress on the site's Progress page (`/progress/`), then import it on the new address. Use the same export and import to move between phone and laptop.
