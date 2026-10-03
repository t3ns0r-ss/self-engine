// Browser test of every real lesson (PLAN.md Section 17.1): renders without errors, shows the
// counts from its data file, and its interactive parts work. Run via tests/e2e.sh, which builds the
// site without the placeholder topic first.
const fs = require('fs');
const path = require('path');
const { parse } = require('yaml');
const { chromium } = require(process.env.PLAYWRIGHT_PATH || 'playwright');
const BASE = process.env.BASE || 'http://localhost:4321';
const OUT = process.env.SHOTS || path.join(__dirname, '.shots');
fs.mkdirSync(OUT, { recursive: true });
let failures = 0;
const check = (cond, msg) => { console.log(`${cond ? 'ok  ' : 'FAIL'} ${msg}`); if (!cond) failures++; };

const ROOT = path.join(__dirname, '..', '..');
const curriculum = parse(fs.readFileSync(path.join(ROOT, 'src/data/curriculum.yaml'), 'utf8'));
const topicDir = path.join(ROOT, 'src/data/topics');
const topics = fs.readdirSync(topicDir).filter((f) => f.endsWith('.yaml')).map((f) => parse(fs.readFileSync(path.join(topicDir, f), 'utf8')));

(async () => {
  const b = await chromium.launch(process.env.CHROMIUM ? { executablePath: process.env.CHROMIUM } : {});
  if (!topics.length) console.log('no lessons yet');
  for (const tf of topics) {
    // A draft lesson is still being written: its sections may be empty, so it is not tested yet.
    if (tf.draft) {
      console.log(`skip [${tf.id}] (draft)`);
      continue;
    }
    const t = curriculum.find((x) => x.id === tf.id);
    const slug = tf.id.replace('.', '-');
    const lesson = `${BASE}/phase-${t.phase}/${slug}-${t.slug}/`;
    const p = await b.newPage({ viewport: { width: 1200, height: 900 } });
    const errs = [];
    p.on('pageerror', (e) => errs.push(e.message));
    p.on('console', (m) => m.type() === 'error' && errs.push(m.text()));
    await p.goto(lesson);
    await p.waitForSelector('.ladder');
    const T = `[${tf.id}]`;
    check(await p.locator('.katex-error').count() === 0, `${T} no KaTeX errors`);
    check(await p.locator('.draft-note').count() === (tf.draft ? 1 : 0), `${T} draft notice matches the data file`);
    check(await p.locator('.recognition-card').count() === tf.cards.length, `${T} ${tf.cards.length} recognition cards`);
    const ladderCards = new Set(tf.problems.filter((x) => x.role === 'ladder').map((x) => x.card));
    check(await p.locator('.ladder-group').count() === ladderCards.size, `${T} ${ladderCards.size} ladder groups`);
    check(await p.locator('.drill li').count() === tf.drill.length, `${T} ${tf.drill.length} drill items`);

    // First ladder problem: hint 1 behind the struggle-budget reminder.
    // The ladder is shown in card order, so the first item is rung 1 of the first card that has rungs.
    const firstCard = tf.cards.find((c) => tf.problems.some((x) => x.role === 'ladder' && x.card === c.id));
    const first = tf.problems.find((x) => x.role === 'ladder' && x.card === firstCard.id && x.rung === 1);
    const item = p.locator('.ladder-item').first();
    await item.locator('button:has-text("Hint 1")').click();
    check(await item.locator('text=Struggle budget').isVisible(), `${T} hint 1 shows the reminder`);
    await item.locator('button:has-text("Show hint 1")').click();
    check(await item.locator(`text=${first.hints[0].slice(0, 40)}`).isVisible(), `${T} hint 1 text revealed`);

    // Log a solve.
    await item.locator('button:has-text("Log")').click();
    await item.locator('select[id$=status]').selectOption('solved');
    await item.locator('button:has-text("Save")').click();
    await p.waitForTimeout(200);
    check(await p.locator('.ladder-group').first().locator('text=/1 \\/ \\d+ solved/').isVisible(), `${T} progress bar counts the solve`);

    // Drill: answer every item with its correct card, then check the score.
    const items = p.locator('.drill li');
    for (let i = 0; i < tf.drill.length; i++) {
      const d = tf.drill[i];
      const it = items.nth(i);
      await it.locator('select').selectOption(`${d.answer_topic}:${d.answer_card}`);
      await it.locator('input').fill('property');
      await it.locator('button:has-text("Reveal")').click();
    }
    await p.waitForTimeout(200);
    check(await p.locator('.drill li.drill-right').count() === tf.drill.length, `${T} every drill answer is selectable and marked right`);

    // Checkpoint timer and pass.
    check(await p.locator('.checkpoint a').count() === 0, `${T} checkpoint problems hidden before start`);
    await p.locator(`button:has-text("Start the ${tf.checkpoint.time_limit_minutes}-minute checkpoint")`).click();
    check(await p.locator('.timer').isVisible(), `${T} checkpoint timer runs`);
    check(await p.locator('.checkpoint a').count() === 3, `${T} checkpoint shows 3 problems after start`);
    await p.locator('button:has-text("done early")').click();
    const boxes = p.locator('.checkpoint input[type=checkbox]');
    await boxes.nth(0).check();
    await boxes.nth(1).check();
    await p.locator('button:has-text("Submit results")').click();
    await p.waitForTimeout(200);
    check(await p.locator('text=Passed on').isVisible(), `${T} checkpoint passes`);
    for (const s of [1, 2, 3]) check(await p.locator(`a[href$="/review/${slug}/${s}/"]`).isVisible(), `${T} review set ${s} linked with its due date`);
    await p.locator('.sl-markdown-content').screenshot({ path: `${OUT}/lesson-${slug}.png` });

    // Review set 1: due date, reveal, no hints.
    await p.goto(`${BASE}/review/${slug}/1/`);
    await p.waitForSelector('.review');
    check(await p.locator('text=Due on').isVisible(), `${T} review page shows the due date`);
    check(await p.locator('button:has-text("Hint"), .hint').count() === 0, `${T} review page has no hints`);
    const reviewCount = tf.problems.filter((x) => x.role === 'review' && x.review_set === 1).length;
    check(await p.locator('button:has-text("Reveal tool")').count() === reviewCount, `${T} review set 1 has ${reviewCount} problems`);
    check(errs.length === 0, `${T} no browser errors ${errs.length ? JSON.stringify(errs) : ''}`);
    await p.close();

    // Narrow mobile width, dark theme.
    const m = await b.newPage({ viewport: { width: 375, height: 800 }, colorScheme: 'dark' });
    await m.goto(lesson);
    await m.waitForSelector('.ladder');
    check(!(await m.evaluate(() => document.documentElement.scrollWidth > window.innerWidth)), `${T} no horizontal page scroll at 375px`);
    await m.screenshot({ path: `${OUT}/lesson-${slug}-mobile.png` });
    await m.close();
  }
  await b.close();
  console.log(failures ? `${failures} check(s) failed` : 'all lesson checks passed');
  process.exit(failures ? 1 : 0);
})();
