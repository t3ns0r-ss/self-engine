# CP Training

A self-study competitive programming site (Astro + Starlight). The full plan is in `PLAN.md`. The problem bank plan is in `PROBLEM_BANK_PLAN.md`. Current status is in `PROGRESS.md`.

## Run locally
```
npm install
npm run dev                         # live editing at http://localhost:4321
npm run build && npm run preview    # check the production build
npm test                            # validator tests
```
`npm run build` first validates all data (`npm run validate`) and checks that `problem-bank/` is up to date. Then it builds the site into `dist/`.

## Where things live
| Path | What |
|---|---|
| `src/data/curriculum.yaml` | the 48 topics, in order |
| `src/data/bank/patterns/{id}.yaml` | the patterns for each topic (a pattern is a named sub-type of the topic's technique, with the precondition that makes it work) |
| `src/data/bank/{id}.yaml` | the problems for each topic: practice and reserved sets |
| `notes/bank/{id}.md` | solution notes for every bank problem (not shown on the site) |
| `problem-bank/` | readable lists generated from the bank; regenerate with `npm run bank:md`, never edit by hand |
| `src/lib/schemas.mjs`, `src/lib/validate.mjs` | data schemas and cross-file checks |
| `src/lib/storage.ts` | your progress, kept in browser `localStorage` |

## Your progress is tied to the site's address
Progress lives in your browser and belongs to one exact address (protocol + domain + port). If you move the site to a new domain, or switch between `http` and `https`, export your progress first and import it on the new address. (The export/import page is part of milestone M0.)
