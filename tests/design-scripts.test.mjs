// Tests for scripts/change_cost.sh, scripts/test_design.sh and scripts/exercise_kit_check.sh
// (DESIGN_TRACKS_PLAN.md Sections 9.4, 9.7, 9.8). The units are tiny synthetic Python programs, so no .NET is needed.
// Expected output is derived by hand in the comments, not copied from the scripts.
import { test } from 'node:test';
import assert from 'node:assert/strict';
import { spawnSync, execFileSync } from 'node:child_process';
import { mkdtempSync, mkdirSync, writeFileSync, readFileSync, cpSync, rmSync, renameSync, existsSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join, resolve } from 'node:path';

const SCRIPTS = resolve(import.meta.dirname, '..', 'scripts');
const tmp = () => mkdtempSync(join(tmpdir(), 'design-'));
const sh = (script, args, opts = {}) => spawnSync('bash', [join(SCRIPTS, script), ...args], { encoding: 'utf8', ...opts });
const write = (p, s) => { mkdirSync(join(p, '..'), { recursive: true }); writeFileSync(p, s); };
const git = (cwd, ...a) => execFileSync('git', a, { cwd, encoding: 'utf8' });

// ---------------------------------------------------------------- change_cost.sh
const PLAIN_FEE = `def fee(plan, minutes):
    if plan == "HOURLY":
        return 20 * ((minutes + 59) // 60)
    if plan == "DAILY":
        return 100 * ((minutes + 1439) // 1440)
    raise ValueError(plan)
`;
// Same assertions before and after every scenario; WEEKEND and FREE30 checks apply only when the feature exists.
const TEST_SH = `#!/usr/bin/env bash
set -e
cd "$1"
echo "build chatter that must not reach the measurement table"
python3 -c "
import fee
assert fee.fee('HOURLY', 120) == 40
assert fee.fee('DAILY', 1441) == 200
"
`;

/** Builds a variant dir: base/ from files, test.sh, and scenarios made with a real git diff (never by hand). */
function makeVariant(root, name, baseFiles, edits, testSh = TEST_SH) {
  const v = join(root, name);
  for (const [f, s] of Object.entries(baseFiles)) write(join(v, 'base', f), s);
  write(join(v, 'test.sh'), testSh);
  const work = join(root, `${name}-work`);
  cpSync(join(v, 'base'), work, { recursive: true });
  git(work, 'init', '-q'); git(work, 'config', 'user.email', 't@e'); git(work, 'config', 'user.name', 't');
  git(work, 'add', '-A'); git(work, 'commit', '-qm', 'base');
  mkdirSync(join(v, 'scenarios'));
  for (const [pname, apply] of edits) {
    apply(work);
    git(work, 'add', '-A');
    writeFileSync(join(v, 'scenarios', pname), git(work, 'diff', '--cached', '--no-renames', '--binary'));
    git(work, 'commit', '-qm', pname);
  }
  return v;
}

test('change_cost: plain design, two scenarios, build chatter excluded', () => {
  const root = tmp();
  const v = makeVariant(root, 'plain', { 'fee.py': PLAIN_FEE }, [
    ['01-weekend.patch', (w) => write(join(w, 'fee.py'), PLAIN_FEE.replace('    raise', '    if plan == "WEEKEND":\n        return 40 * ((minutes + 59) // 60)\n    raise')) ],
    ['02-free30.patch', (w) => write(join(w, 'fee.py'), readFileSync(join(w, 'fee.py'), 'utf8').replace('return 20 * ((minutes + 59) // 60)', 'return 20 * ((max(minutes - 30, 0) + 59) // 60)')) ],
  ]);
  const r = sh('change_cost.sh', [v]);
  assert.equal(r.status, 0, r.stderr);
  // base: 1 file; non-blank lines of PLAIN_FEE = 6.
  // 01: fee.py modified, +2 lines, -0; no new files. 02: one line replaced: +1 / -1.
  assert.equal(r.stdout,
    'base\tfiles=1\tnonblank_lines=6\n' +
    'scenario\tfiles_modified\tfiles_added\tfiles_deleted\tlines_added_in_modified\tlines_removed_in_modified\tlines_in_new_files\n' +
    '01-weekend\t1\t0\t0\t2\t0\t0\n' +
    '02-free30\t1\t0\t0\t1\t1\t0\n');
  assert.ok(!r.stdout.includes('chatter'));
});

test('change_cost: added file counts its lines; a file without a final newline counts correctly', () => {
  const root = tmp();
  const v = makeVariant(root, 'strategy', { 'fee.py': 'def fee():\n    return 1', 'wire.py': 'x = 1\n' }, [
    // new file: 3 lines, the last without a final newline
    ['01-new.patch', (w) => write(join(w, 'weekend.py'), 'class W:\n    pass\nW()')],
  ], '#!/usr/bin/env bash\ntrue\n');
  const r = sh('change_cost.sh', [v]);
  assert.equal(r.status, 0, r.stderr);
  // base: 2 files, 2 + 1 = 3 non-blank lines (fee.py has no final newline: awk still counts its 2 lines).
  assert.equal(r.stdout.split('\n')[0], 'base\tfiles=2\tnonblank_lines=3');
  assert.equal(r.stdout.split('\n')[2], '01-new\t0\t1\t0\t0\t0\t3');
});

test('change_cost: a rename is one deletion plus one addition', () => {
  const root = tmp();
  const v = makeVariant(root, 'ren', { 'a.py': 'one\ntwo\nthree\n', 'b.py': 'x\n' }, [
    ['01-rename.patch', (w) => renameSync(join(w, 'a.py'), join(w, 'c.py'))],
  ], '#!/usr/bin/env bash\ntrue\n');
  const r = sh('change_cost.sh', [v]);
  assert.equal(r.status, 0, r.stderr);
  assert.equal(r.stdout.split('\n')[2], '01-rename\t0\t1\t1\t0\t0\t3'); // c.py is new with 3 lines; a.py deleted
});

test('change_cost: failing test.sh exits non-zero with the log on stderr', () => {
  const root = tmp();
  const v = makeVariant(root, 'bad', { 'a.py': 'x = 1\n' }, [
    ['01-break.patch', (w) => write(join(w, 'a.py'), 'x = 2\n')],
  ], '#!/usr/bin/env bash\ngrep -q "x = 1" "$1/a.py" || { echo "LOGLINE assertion failed"; exit 1; }\n');
  const r = sh('change_cost.sh', [v]);
  assert.notEqual(r.status, 0);
  assert.match(r.stderr, /FAIL: tests fail after 01-break\.patch/);
  assert.match(r.stderr, /LOGLINE assertion failed/);
});

test('change_cost: a binary file in a scenario is refused', () => {
  const root = tmp();
  const v = makeVariant(root, 'bin', { 'a.py': 'x = 1\n' }, [
    ['01-bin.patch', (w) => writeFileSync(join(w, 'blob.bin'), Buffer.from([0, 1, 2, 255, 0, 7]))],
  ], '#!/usr/bin/env bash\ntrue\n');
  const r = sh('change_cost.sh', [v]);
  assert.notEqual(r.status, 0);
  assert.match(r.stderr, /binary file in scenario 01-bin\.patch/);
});

// ---------------------------------------------------------------- test_design.sh
test('test_design: claim/calc outputs, pattern units and missing files', () => {
  const root = tmp();
  const code = join(root, 'code');
  // passing check.py
  write(join(code, 'H1.1', 'claim-1', 'check.py'), 'print("N=1: ok")\n');
  write(join(code, 'H1.1', 'claim-1', 'expected.txt'), 'N=1: ok\n');
  // passing calc.py
  write(join(code, 'H1.1', 'calc-a', 'calc.py'), 'print("x = 3 items")\n');
  write(join(code, 'H1.1', 'calc-a', 'expected.txt'), 'x = 3 items\n');
  // pattern unit with correct measured file
  const pu = join(code, 'L2.1', 'pat');
  const v = makeVariant(pu, 'plain', { 'a.py': 'x = 1\n' }, [['01-b.patch', (w) => write(join(w, 'a.py'), 'x = 1\ny = 2\n')]], '#!/usr/bin/env bash\ntrue\n');
  write(join(pu, 'unit.yaml'), 'kind: pattern\ndomain: demo\nvariants: [plain]\n');
  const table = sh('change_cost.sh', [v]).stdout;
  rmSync(join(pu, 'plain-work'), { recursive: true });
  write(join(pu, 'measured-plain.tsv'), table);

  let r = sh('test_design.sh', [code]);
  assert.equal(r.status, 0, r.stdout + r.stderr);
  assert.equal(r.stdout.trim(), 'All design code units passed');

  // wrong expected output is reported
  write(join(code, 'H1.1', 'claim-1', 'expected.txt'), 'N=1: bad\n');
  r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /FAIL \(output differs from expected\.txt\): .*claim-1/);
  write(join(code, 'H1.1', 'claim-1', 'expected.txt'), 'N=1: ok\n');

  // stale measured file is reported
  write(join(pu, 'measured-plain.tsv'), table.replace('base\tfiles=1', 'base\tfiles=9'));
  r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /measured-plain\.tsv is out of date/);
  write(join(pu, 'measured-plain.tsv'), table);

  // missing expected.txt
  rmSync(join(code, 'H1.1', 'calc-a', 'expected.txt'));
  r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /MISSING expected\.txt: .*calc-a/);
});

test('test_design: a pattern unit without variants, and a .sln when dotnet is missing, both fail', () => {
  const root = tmp();
  const code = join(root, 'code');
  write(join(code, 'L1.1', 'p', 'unit.yaml'), 'kind: pattern\ndomain: demo\n');
  let r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /MISSING variants/);

  rmSync(join(code, 'L1.1'), { recursive: true });
  write(join(code, 'L1.2', 'sol', 'Sol.sln'), '');
  // PATH with only the tools the script needs, none of which is dotnet
  const bin = join(root, 'bin'); mkdirSync(bin);
  for (const t of ['bash', 'find', 'sort', 'dirname', 'grep', 'sed', 'tr', 'diff', 'mktemp', 'rm', 'cat', 'python3']) {
    const p = spawnSync('bash', ['-c', `command -v ${t}`], { encoding: 'utf8' }).stdout.trim();
    if (p) spawnSync('ln', ['-s', p, join(bin, t)]);
  }
  r = sh('test_design.sh', [code], { env: { PATH: bin } });
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /dotnet not installed; cannot test .*Sol\.sln/);
});

// ---------------------------------------------------------------- exercise_kit_check.sh
// The kit's test.sh succeeds when the solution's answer.txt contains the word RIGHT.
const KIT_TEST = '#!/usr/bin/env bash\ngrep -q RIGHT "$1/answer.txt"\n';

function makeKitRoot({ rel = 'L2.1/ex-1', starter = 'WRONG', reference = 'RIGHT', mutants = ['WRONG', 'WRONG', 'WRONG'], minMutants } = {}) {
  const root = tmp();
  const ex = join(root, 'exercises'), ref = join(root, 'reference'), mut = join(root, 'reference-mutants');
  write(join(ex, rel, 'test.sh'), KIT_TEST);
  write(join(ex, rel, 'starter', 'answer.txt'), starter);
  write(join(ref, rel, 'answer.txt'), reference);
  mutants.forEach((m, i) => write(join(mut, rel, `m${i + 1}`, 'answer.txt'), m));
  if (minMutants !== undefined) write(join(ex, rel, 'min_mutants'), String(minMutants));
  return { root, ex, ref, mut };
}
const kit = (k, exArg) => sh('exercise_kit_check.sh', [exArg ?? k.ex, k.ref, k.mut]);

test('kit check: a consistent kit passes', () => {
  const k = makeKitRoot();
  const r = kit(k);
  assert.equal(r.status, 0, r.stdout + r.stderr);
  assert.equal(r.stdout.trim(), 'All exercise kits consistent');
});
test('kit check: reference that fails', () => {
  const r = kit(makeKitRoot({ reference: 'WRONG' }));
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /reference does not pass: L2\.1\/ex-1/);
});
test('kit check: starter that passes means tests too weak', () => {
  const r = kit(makeKitRoot({ starter: 'RIGHT' }));
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /tests pass on the starter: L2\.1\/ex-1/);
});
test('kit check: a mutant that passes', () => {
  const r = kit(makeKitRoot({ mutants: ['WRONG', 'RIGHT', 'WRONG'] }));
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /tests pass on mutant L2\.1\/ex-1\/m2 \(tests too weak\)/);
});
test('kit check: too few mutants', () => {
  const r = kit(makeKitRoot({ mutants: ['WRONG', 'WRONG'] }));
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /2 mutants for L2\.1\/ex-1, need 3/);
});
test('kit check: a ladder rung with min_mutants set to 1 passes with one mutant', () => {
  const k = makeKitRoot({ rel: 'L2.1/ladder/rung-2', mutants: ['WRONG'], minMutants: 1 });
  const r = kit(k);
  assert.equal(r.status, 0, r.stdout + r.stderr);
});
test('kit check: a root given with a trailing slash works', () => {
  const k = makeKitRoot();
  const r = kit(k, k.ex + '/');
  assert.equal(r.status, 0, r.stdout + r.stderr);
});
test('kit check: missing starter and missing reference are reported', () => {
  const k = makeKitRoot();
  rmSync(join(k.ex, 'L2.1/ex-1/starter'), { recursive: true });
  let r = kit(k);
  assert.match(r.stdout, /MISSING starter: L2\.1\/ex-1/);
  write(join(k.ex, 'L2.1/ex-1/starter/answer.txt'), 'WRONG');
  rmSync(join(k.ref, 'L2.1/ex-1'), { recursive: true });
  r = kit(k);
  assert.match(r.stdout, /MISSING reference: L2\.1\/ex-1/);
  assert.ok(existsSync(k.ref));
});
