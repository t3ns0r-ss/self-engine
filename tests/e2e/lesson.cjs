// Browser test of the lesson components on the placeholder topic. Run via tests/e2e.sh.
const { chromium } = require(process.env.PLAYWRIGHT_PATH || 'playwright');
const BASE = process.env.BASE || 'http://localhost:4321';
const OUT = process.env.SHOTS || require('path').join(__dirname, '.shots');
require('fs').mkdirSync(OUT, { recursive: true });
let failures = 0;
const check = (cond, msg) => { console.log(`${cond ? 'ok  ' : 'FAIL'} ${msg}`); if (!cond) failures++; };

(async () => {
  const b = await chromium.launch(process.env.CHROMIUM ? { executablePath: process.env.CHROMIUM } : {});
  const p = await b.newPage({ viewport: { width: 1200, height: 900 } });
  const errs = [];
  p.on('pageerror', (e) => errs.push(e.message));
  p.on('console', (m) => m.type() === 'error' && errs.push(m.text()));
  await p.goto(`${BASE}/phase-1/1-3-two-pointers/`);
  await p.waitForSelector('.ladder');
  check(await p.locator('.katex').count() >= 2, 'KaTeX renders inline and display math');
  check(await p.locator('pre:has-text("sum -= a[l++]")').count() === 1, 'tested code is shown');
  check(await p.locator('.recognition-card').count() === 3, 'three recognition cards');
  check(await p.locator('.ladder-group').count() === 3, 'three ladder groups');
  check(await p.locator('text=More practice').count() === 1, '"More practice" lists unused bank problems');

  // Hints: reminder first, then reveal; count recorded.
  const first = p.locator('.ladder-item').first();
  await first.locator('button:has-text("Hint 1")').click();
  check(await first.locator('text=Struggle budget').isVisible(), 'hint 1 shows the struggle-budget reminder');
  await first.locator('button:has-text("Show hint 1")').click();
  check(await first.locator('text=Placeholder hint one.').isVisible(), 'hint 1 revealed');
  await first.locator('button:has-text("Hint 2")').click();
  check(await first.locator('text=at least 10 minutes').isVisible(), 'hint 2 reminder mentions 10 minutes');
  await first.locator('button:has-text("Show hint 2")').click();
  check(await first.locator('text=2 hints opened').isVisible(), 'hints opened recorded');

  // Log a problem.
  await first.locator('button:has-text("Log")').click();
  await first.locator('select[id$=status]').selectOption('solved_hints');
  await first.locator('button:has-text("Save")').click();
  await p.waitForTimeout(200);
  check(await p.locator('.ladder-group').first().locator('text=1 / 4 solved').isVisible(), 'progress bar counts the solve');

  // Drill: answer every item correctly.
  const items = p.locator('.drill li');
  const n = await items.count();
  check(n === 8, `drill has 8 items (got ${n})`);
  for (let i = 0; i < n; i++) {
    const it = items.nth(i);
    const answer = (await it.locator('p').nth(1).textContent()).includes('negative') ? '1.2:prefix-count-lookup' : '1.3:shrinkable-window';
    await it.locator('select').selectOption(answer);
    await it.locator('input').fill('placeholder property');
    await it.locator('button:has-text("Reveal")').click();
  }
  await p.waitForTimeout(200);
  check(await p.locator('.drill li.drill-right').count() === 8, 'all drill items marked right');
  check(await p.locator('text=Score: 8 right out of 8').isVisible(), 'drill score shown');

  // Checkpoint: hidden until start, timer, finish, pass.
  check(await p.locator('.checkpoint a').count() === 0, 'checkpoint problems hidden before start');
  await p.locator('button:has-text("Start the 90-minute checkpoint")').click();
  check(await p.locator('.timer').isVisible(), 'timer runs');
  const t0 = await p.locator('.timer').textContent();
  check(/1:29:5\d|1:30:00/.test(t0), `timer counts down from 90 minutes (${t0})`);
  await p.reload();
  await p.waitForSelector('.timer');
  check(true, 'timer survives a reload');
  await p.locator('button:has-text("done early")').click();
  const boxes = p.locator('.checkpoint input[type=checkbox]');
  await boxes.nth(0).check();
  await boxes.nth(1).check();
  await p.locator('button:has-text("Submit results")').click();
  await p.waitForTimeout(200);
  check(await p.locator('text=Passed on').isVisible(), 'checkpoint passes with 2/3 and 8 drill items');
  check(await p.locator('a[href$="/review/1-3/1/"]').isVisible(), 'review set links shown with due dates');

  await p.locator('.sl-markdown-content').screenshot({ path: `${OUT}/lesson.png` });

  // Review page: due date, reveal, no hints.
  await p.goto(`${BASE}/review/1-3/1/`);
  await p.waitForSelector('.review');
  check(await p.locator('text=Due on').isVisible(), 'review page shows the due date');
  check(await p.locator('button:has-text("Hint"), .hint').count() === 0, 'review page has no hints');
  await p.locator('button:has-text("Reveal tool")').first().click();
  check(await p.locator('text=Placeholder decisive property').first().isVisible(), 'review reveal shows tool and property');

  // Mobile and dark theme.
  const m = await b.newPage({ viewport: { width: 375, height: 800 }, colorScheme: 'dark' });
  await m.goto(`${BASE}/phase-1/1-3-two-pointers/`);
  await m.waitForSelector('.ladder');
  check(!(await m.evaluate(() => document.documentElement.scrollWidth > window.innerWidth)), 'no horizontal page scroll at 375px');
  await m.screenshot({ path: `${OUT}/lesson-mobile.png`, fullPage: false });

  check(errs.length === 0, `no browser errors ${errs.length ? JSON.stringify(errs) : ''}`);
  await b.close();
  console.log(failures ? `${failures} check(s) failed` : 'all browser checks passed');
  process.exit(failures ? 1 : 0);
})();
