// Browser test of the dashboard and generated pages on the placeholder topic. Run via tests/e2e.sh.
const { chromium } = require(process.env.PLAYWRIGHT_PATH || 'playwright');
const fs = require('fs');
const path = require('path');
const BASE = process.env.BASE || 'http://localhost:4321';
const OUT = process.env.SHOTS || path.join(__dirname, '.shots');
fs.mkdirSync(OUT, { recursive: true });
let failures = 0;
const check = (cond, msg) => { console.log(`${cond ? 'ok  ' : 'FAIL'} ${msg}`); if (!cond) failures++; };
const daysAgo = (n) => new Date(Date.now() - n * 864e5).toISOString().slice(0, 10);

(async () => {
  const b = await chromium.launch(process.env.CHROMIUM ? { executablePath: process.env.CHROMIUM } : {});
  const ctx = await b.newContext({ viewport: { width: 1200, height: 900 }, acceptDownloads: true });
  const p = await ctx.newPage();
  const errs = [];
  p.on('pageerror', (e) => errs.push(e.message));
  p.on('console', (m) => m.type() === 'error' && errs.push(m.text()));

  await p.goto(`${BASE}/`);
  await p.waitForSelector('.dashboard');
  check(await p.locator('text=No current topic yet').isVisible(), 'dashboard with empty storage');
  check(await p.locator('.dashboard a:has-text("0.1")').isVisible(), 'next step points at the first topic');

  await p.goto(`${BASE}/phase-1/1-3-two-pointers/`);
  await p.locator('button:has-text("Make this my current topic")').click();
  await p.goto(`${BASE}/`);
  await p.waitForSelector('.dashboard');
  check(await p.locator('text=0 / 12 ladder problems solved').isVisible(), 'dashboard shows current topic progress');
  check(await p.locator('text=finish rung 1 of Shrinkable window').isVisible(), 'next step names the first unsolved rung in card order');
  await p.locator('summary:has-text("Phase 1")').first().click().catch(() => {});
  check(await p.locator('a[data-topic="1.4"] .later-badge').count() === 1, 'sidebar marks later topics');
  check(await p.locator('a[data-topic="1.2"] .later-badge').count() === 0, 'sidebar does not mark earlier topics');

  // Seed history: a problem read with the editorial 8 days ago (re-solve due), with a recognition miss,
  // and a checkpoint passed 4 days ago (review set 1 due).
  const ids = await p.evaluate(async () => (await (await fetch('/phase-1/1-3-two-pointers/')).text()).match(/cf-90\d\dA/g));
  const ladderId = 'cf-9001A';
  await p.evaluate(({ ladderId, d8, d4 }) => {
    localStorage.setItem('cp:v1:problems', JSON.stringify({ [ladderId]: { status: 'editorial', hintsOpened: 3, mistake: 'recognition', date: d8, note: 'missed closure' } }));
    localStorage.setItem('cp:v1:topics', JSON.stringify({ '1.3': { started: d8, checkpointPassedOn: d4 } }));
  }, { ladderId, d8: daysAgo(8), d4: daysAgo(4) });
  await p.reload();
  await p.waitForSelector('.dashboard');
  check(await p.locator('a:has-text("Review set 1 for 1.3")').isVisible(), 'review set 1 due after 3 days');
  check(await p.locator('a:has-text("Review set 2")').count() === 0, 'review set 2 not yet due');
  check(await p.locator('.dashboard a:has-text("Placeholder Problem 1")').isVisible(), 're-solve listed 7 days after reading the editorial');
  check(await p.locator('text=Recognition miss: 1').isVisible(), 'mistake summary counts');
  check(await p.locator('text=Shrinkable window (1.3) ×1').isVisible(), 'card with most recognition misses');
  check(!!ids, 'lesson HTML contains problem ids');

  // Problems page: hidden roles appear after the checkpoint.
  await p.goto(`${BASE}/problems/`);
  await p.waitForSelector('.bank-table');
  check(await p.locator('td:has-text("checkpoint")').count() === 3, 'checkpoint problems visible after passing');
  await p.evaluate(() => localStorage.setItem('cp:v1:topics', '{}'));
  await p.reload();
  await p.waitForSelector('.bank-table');
  check(await p.locator('td:has-text("checkpoint")').count() === 0, 'checkpoint problems hidden before passing');
  check(await p.locator('text=hidden until their topic').isVisible(), 'hidden count explained');
  await p.locator('select[aria-label=Role]').selectOption('ladder');
  check(await p.locator('tbody tr').count() === 12, 'role filter');
  await p.locator('button.th-sort:has-text("Difficulty")').click();
  await p.locator('button.th-sort:has-text("Difficulty")').click();
  check((await p.locator('tbody tr').first().textContent()).includes('1600'), 'sort by difficulty, descending');

  // Handbook.
  await p.goto(`${BASE}/handbook/`);
  await p.waitForSelector('.handbook');
  check(await p.locator('h3:has-text("Longest/shortest contiguous segment")').isVisible(), 'handbook groups by weak signal');
  await p.locator('button:has-text("By topic")').click();
  check(await p.locator('.recognition-card').count() === 3, 'handbook lists cards by topic');
  await p.locator('button:has-text("Flashcards")').click();
  await p.locator('button:has-text("Show the card")').click();
  check(await p.locator('.flashcard:has-text("Decisive property")').count() === 1, 'flashcard flips');

  // Glossary.
  await p.goto(`${BASE}/glossary/`);
  check(await p.locator('dt:has-text("GCD")').isVisible() && await p.locator('text=greatest common divisor').isVisible(), 'glossary shows expansions');
  check(await p.locator('a:has-text("Introduced in 1.3")').isVisible(), 'glossary links the introducing lesson');

  // Contest log.
  await p.goto(`${BASE}/contests/`);
  await p.waitForSelector('.contest-form');
  await p.locator('.contest-form label:has-text("Name") input').fill('Test Contest 1');
  await p.locator('.contest-form textarea').first().fill('abc999_d, abc999_e');
  await p.locator('button:has-text("Add contest")').click();
  check(await p.locator('#upsolve + ul li').count() === 2, 'upsolve targets listed');
  await p.locator('.upsolve-list input').first().check();
  check(await p.locator('#upsolve + ul li').count() === 1, 'ticking a target removes it from the open list');

  // Progress: export, reset, import, feedback.
  await p.goto(`${BASE}/progress/`);
  await p.evaluate((ladderId) => localStorage.setItem('cp:v1:problems', JSON.stringify({ [ladderId]: { status: 'editorial', hintsOpened: 3, mistake: 'recognition', date: '2026-01-01', note: 'missed closure' } })), ladderId);
  const [dl] = await Promise.all([p.waitForEvent('download'), p.locator('button:has-text("Export progress")').click()]);
  const file = path.join(OUT, 'export.json');
  await dl.saveAs(file);
  const exported = JSON.parse(fs.readFileSync(file, 'utf8'));
  check(exported.format === 'cp-training-progress' && exported['cp:v1:problems'][ladderId], 'export contains the data');
  p.on('dialog', (d) => d.accept());
  await p.locator('button:has-text("Reset all progress")').click();
  check(await p.evaluate(() => localStorage.getItem('cp:v1:problems')) === null, 'reset clears storage');
  await p.locator('input[type=file]').setInputFiles(file);
  await p.waitForTimeout(300);
  check((await p.evaluate(() => localStorage.getItem('cp:v1:problems')) || '').includes(ladderId), 'import restores data');
  const bad = path.join(OUT, 'bad.json');
  fs.writeFileSync(bad, '{"hello": 1}');
  await p.locator('input[type=file]').setInputFiles(bad);
  await p.waitForTimeout(300);
  check(await p.locator('text=not a CP Training progress export').isVisible(), 'import rejects other files');
  await p.locator('button:has-text("Copy feedback")').click();
  await p.waitForTimeout(300);
  const fb = await p.locator('.feedback-box').inputValue();
  check(/## \d{4}-\d{2}-\d{2} — topic 1\.3\n- Type: confusing\n- Where: card Shrinkable window \(problems cf-9001A\)\n- What: 1 × Recognition miss\. Notes: cf-9001A: missed closure\n- Status: open/.test(fb), 'feedback snippet in FEEDBACK.md format');

  // Method page.
  await p.goto(`${BASE}/method/`);
  check(await p.locator('.katex').count() > 0, 'method page renders math');

  const m = await b.newPage({ viewport: { width: 375, height: 800 }, colorScheme: 'dark' });
  for (const u of ['/', '/problems/', '/handbook/', '/progress/', '/contests/']) {
    await m.goto(`${BASE}${u}`);
    await m.waitForTimeout(300);
    check(!(await m.evaluate(() => document.documentElement.scrollWidth > window.innerWidth)), `no horizontal page scroll at 375px on ${u}`);
  }
  check(errs.length === 0, `no browser errors ${errs.length ? JSON.stringify(errs) : ''}`);
  await b.close();
  console.log(failures ? `${failures} check(s) failed` : 'all page checks passed');
  process.exit(failures ? 1 : 0);
})();
