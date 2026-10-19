// Browser test of the design components on the placeholder topics (DESIGN_TRACKS_PLAN.md Section 11.7), at desktop
// width and at 375 pixels: no console errors, no horizontal scrolling, and each interactive part works.
const fs = require('fs');
const path = require('path');
const { chromium } = require(process.env.PLAYWRIGHT_PATH || 'playwright');
const BASE = process.env.BASE || 'http://localhost:4329/self-engine';
const OUT = process.env.SHOTS || path.join(__dirname, '.shots');
fs.mkdirSync(OUT, { recursive: true });
let failures = 0;
const check = (cond, msg) => { console.log(`${cond ? 'ok  ' : 'FAIL'} ${msg}`); if (!cond) failures++; };

(async () => {
  const b = await chromium.launch(process.env.CHROMIUM ? { executablePath: process.env.CHROMIUM } : {});
  for (const [label, width] of [['desktop', 1200], ['375px', 375]]) {
    const ctx = await b.newContext({ viewport: { width, height: 900 } });
    const pages = [
      ['HLD lesson', '/hld/phase-4/h4-2-quorums/'], ['LLD lesson', '/lld/phase-2/l2-1-strategy/'],
      ['HLD exercise rung', '/hld/exercise/H4.2/rung-1/'], ['HLD estimate', '/hld/exercise/H4.2/est-1/'], ['LLD exercise rung', '/lld/exercise/L2.1/rung-1/'],
      ['LLD handbook', '/lld/handbook/'], ['HLD handbook', '/hld/handbook/'], ['labs', '/hld/labs/'], ['numbers', '/hld/numbers/'],
    ];
    for (const [name, p] of pages) {
      const page = await ctx.newPage();
      const errs = [];
      page.on('pageerror', (e) => errs.push(e.message));
      page.on('console', (m) => m.type() === 'error' && errs.push(m.text()));
      await page.goto(BASE + p, { waitUntil: 'networkidle' });
      const over = await page.evaluate(() => document.documentElement.scrollWidth - document.documentElement.clientWidth);
      check(errs.length === 0, `[${label}] ${name}: no console errors${errs.length ? ' ' + errs[0] : ''}`);
      check(over <= 1, `[${label}] ${name}: no horizontal scroll (${over}px)`);
      if (name === 'HLD lesson') await page.screenshot({ path: path.join(OUT, `design-hld-${label.replace('px', '')}.png`), fullPage: true });
      await page.close();
    }
    await ctx.close();
  }

  // ---- D10: the lesson's Mermaid diagram is an SVG image, rendered at build time ----
  {
    const c = await b.newContext({ viewport: { width: 1200, height: 900 } });
    const p = await c.newPage();
    await p.goto(BASE + '/lld/phase-2/l2-1-strategy/', { waitUntil: 'networkidle' });
    const n = await p.evaluate(() => [...document.querySelectorAll('img')].filter((i) => i.src.startsWith('data:image/svg+xml') && i.naturalWidth > 0).length);
    check(n === 1, 'LLD lesson: Mermaid diagram rendered as an SVG image that loads');
    await c.close();
  }

  // ---- interactions at desktop width ----
  const ctx = await b.newContext({ viewport: { width: 1200, height: 900 } });
  let page = await ctx.newPage();
  await page.goto(BASE + '/hld/phase-4/h4-2-quorums/', { waitUntil: 'networkidle' });
  await page.waitForSelector('.design-ladder li');
  check(await page.locator('.design-ladder li').count() === 1, 'ladder list shows the 1 practice rung from the JSON');
  // drill: reserved items are fetched, not in the HTML
  await page.waitForSelector('.drill ol li');
  check(await page.locator('.drill ol li').count() === 2, 'drill shows the 2 reserved items from the JSON');
  const li = page.locator('.drill ol li').first();
  await li.locator('select').selectOption({ index: 1 });
  check(await li.locator('button', { hasText: 'Reveal' }).isDisabled(), 'reveal is disabled until the property sentence is written');
  await li.locator('input').fill('write quorum plus read quorum exceeds replicas');
  await li.locator('button', { hasText: 'Reveal' }).click();
  check(await li.locator('.drill-answer').count() === 1, 'drill reveals the answer after the property is written');
  // checkpoint
  await page.waitForSelector('.checkpoint');
  await page.locator('.checkpoint button', { hasText: 'Start' }).click();
  check(await page.locator('.checkpoint code', { hasText: 'new_attempt.sh H4.2/lab/rung-1' }).count() === 1, 'checkpoint shows the kit commands after start');
  check(await page.locator('.phase-timer').count() === 1 || await page.locator('[role=timer]').count() === 1, 'checkpoint timer is running');
  await page.close();

  page = await ctx.newPage();
  await page.goto(BASE + '/hld/exercise/H4.2/rung-1/', { waitUntil: 'networkidle' });
  const ask = page.locator('.ask-first');
  check(await ask.locator('button', { hasText: 'Reveal' }).isDisabled(), 'ask-first reveal needs some text');
  await ask.locator('textarea').fill('How many replicas?');
  await ask.locator('button', { hasText: 'Reveal' }).click();
  await ask.locator('input[type=checkbox]').first().check();
  check((await ask.textContent()).includes('1 of 2'), 'ask-first counts the critical questions asked');
  check(await page.locator('text=unlocks after you log an attempt').count() === 1, 'reference solution is locked before an attempt');
  await page.locator('.attempt-log label', { hasText: 'The tests pass' }).locator('input').check();
  await page.locator('.attempt-log button', { hasText: 'Save' }).click();
  await page.waitForSelector('details:has-text("Reference solution")');
  check(true, 'reference solution unlocks after an attempt is logged');
  await page.reload({ waitUntil: 'networkidle' });
  check(await page.locator('.attempt-log li').count() === 1, 'the attempt survives a reload (storage)');
  await page.close();

  page = await ctx.newPage();
  await page.goto(BASE + '/hld/exercise/H4.2/est-1/', { waitUntil: 'networkidle' });
  await page.locator('.numeric-answer input').first().fill('5000');
  await page.locator('.numeric-answer button').click();
  check((await page.locator('.numeric-answer').textContent()).includes('Within the factor'), 'numeric answer 5000 vs reference 4200 is within factor 2');
  await page.locator('.numeric-answer input').first().fill('20000');
  await page.locator('.numeric-answer button').click();
  check((await page.locator('.numeric-answer').textContent()).includes('Outside the factor'), 'numeric answer 20000 is outside factor 2');
  await page.close();

  page = await ctx.newPage();
  await page.goto(BASE + '/hld/handbook/', { waitUntil: 'networkidle' });
  check((await page.textContent('.design-handbook')).includes('Quorum replication') || (await page.textContent('.design-handbook')).includes('No entries'), 'handbook renders');
  await page.close();
  await ctx.close();
  await b.close();
  console.log(failures ? `${failures} FAILED` : 'all design browser checks passed');
  process.exit(failures ? 1 : 0);
})();
