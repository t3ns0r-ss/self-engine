// Render check for the 15 restored lessons (LESSON_RESTORE_PLAN.md, Phase 0 step 3).
// Opens each lesson at BASE (default http://localhost:4321), scrolls to the bottom, and counts images, broken images,
// KaTeX errors, ladder items and page errors. Exits 1 if any broken image, KaTeX error or page error is found.
// Usage: npx astro preview --port 4321 &   then   node tests/e2e/render_check.cjs [topic ids]
const fs = require('fs');
const path = require('path');
const { parse } = require('yaml');
const { chromium } = require(process.env.PLAYWRIGHT_PATH || 'playwright');
const BASE = process.env.BASE || 'http://localhost:4321';
const ROOT = path.join(__dirname, '..', '..');
const LESSONS = ['0.1', '0.2', '0.4', '0.6', '1.2', '1.3', '1.4', '1.5', '1.6', '1.7', '2.1', '2.2', '2.3', '2.4', '3.1'];
const ids = process.argv.length > 2 ? process.argv.slice(2) : LESSONS;
const curriculum = parse(fs.readFileSync(path.join(ROOT, 'src/data/curriculum.yaml'), 'utf8'));

(async () => {
  const b = await chromium.launch(process.env.CHROMIUM ? { executablePath: process.env.CHROMIUM } : {});
  let bad = 0;
  for (const id of ids) {
    const t = curriculum.find((x) => x.id === id);
    if (!t) { console.log(`FAIL ${id}: not in curriculum`); bad++; continue; }
    const url = `${BASE}/phase-${t.phase}/${id.replace('.', '-')}-${t.slug}/`;
    const p = await b.newPage({ viewport: { width: Number(process.env.WIDTH || 1200), height: 900 } });
    const errs = [];
    p.on('pageerror', (e) => errs.push(e.message));
    p.on('console', (m) => m.type() === 'error' && errs.push(m.text()));
    await p.goto(url, { waitUntil: 'load', timeout: 120000 });
    await p.waitForSelector('main h1, .sl-markdown-content', { timeout: 120000 });
    // scroll to the bottom in steps so lazy images and islands load
    await p.evaluate(async () => {
      for (let y = 0; y < document.body.scrollHeight; y += 700) { window.scrollTo(0, y); await new Promise((r) => setTimeout(r, 40)); }
      window.scrollTo(0, document.body.scrollHeight);
    });
    await p.waitForTimeout(600);
    const r = await p.evaluate(() => {
      const imgs = [...document.querySelectorAll('main img')];
      return {
        images: imgs.length,
        broken: imgs.filter((i) => i.complete && i.naturalWidth === 0).map((i) => i.getAttribute('src')),
        katexErrors: document.querySelectorAll('.katex-error').length,
        ladder: document.querySelectorAll('.ladder-item').length,
        wide: document.documentElement.scrollWidth > window.innerWidth + 1,
      };
    });
    const fail = r.broken.length || r.katexErrors || errs.length;
    if (fail) bad++;
    console.log(`${fail ? 'FAIL' : 'ok  '} ${id} images=${r.images} broken=${r.broken.length} katexErrors=${r.katexErrors} ladderItems=${r.ladder} pageErrors=${errs.length}${r.wide ? ' (page scrolls sideways)' : ''}`);
    r.broken.forEach((s) => console.log('     broken image:', s));
    errs.slice(0, 3).forEach((e) => console.log('     page error:', e.slice(0, 160)));
    await p.close();
  }
  await b.close();
  process.exit(bad ? 1 : 0);
})();
