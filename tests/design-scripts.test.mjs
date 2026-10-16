// Tests for the design scripts of DESIGN_TRACKS_PLAN.md Section 9: cxxflags.sh, change_cost.sh, test_design.sh,
// exercise_kit_check.sh, new_attempt.sh, labserver.sh, new_kit.mjs. Units are tiny synthetic Go and C++ programs.
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

// ---------------------------------------------------------------- shared fixtures
const REPO = resolve(import.meta.dirname, '..');
const FIX = join(REPO, 'tests', 'fixtures', 'design', 'bucket');
const chmodx = (p) => spawnSync('chmod', ['+x', p]);

/** A code root with go.mod and the shared C++ helper copied from the real repository. */
function codeRoot(root) {
  const code = join(root, 'code');
  write(join(code, 'go.mod'), 'module selfengine/code\n\ngo 1.27\n');
  write(join(code, 'shared', 'go', 'doc', 'doc.go'), 'package doc\n');   // so ./... is never empty
  for (const f of ['check.hpp', 'cxxflags.sh']) {
    write(join(code, 'shared', 'cpp', f), readFileSync(join(REPO, 'code', 'shared', 'cpp', f), 'utf8'));
  }
  return code;
}
const SOLUTION_TEST_SH = readFileSync(join(REPO, 'templates', 'solution-unit-test.sh'), 'utf8');

const COUNTER_HPP = `#pragma once
#include <stdexcept>
class Counter {
public:
    void add(int n) { if (n < 0) throw std::invalid_argument("negative"); total_ += n; }
    int total() const { return total_; }
private:
    int total_ = 0;
};
`;
const PASSING = `
void adds() { Counter c; c.add(2); c.add(3); CHECK(c.total() == 5); }
void rejects_negative() { Counter c; CHECK_THROWS(c.add(-1)); }
void starts_at_zero() { Counter c; CHECK(c.total() == 0); }
`;
const mainOf = (names) => `int main() {\n${names.map((n) => `    RUN(${n});`).join('\n')}\n    return check::report();\n}\n`;
const testsCpp = (body, names) => `#include "check.hpp"\n#include "counter.hpp"\n${body}\n${mainOf(names)}`;

/** A C++ solution unit under code/L1.1/<name>. */
function cppUnit(code, name = 'counter', body = PASSING, names = ['adds', 'rejects_negative', 'starts_at_zero'], marker = null) {
  const d = join(code, 'L1.1', name);
  write(join(d, 'counter.hpp'), COUNTER_HPP);
  write(join(d, 'tests.cpp'), testsCpp(body, names));
  write(join(d, 'unit.yaml'), 'kind: solution\nclaims: []\n');
  write(join(d, 'test.sh'), SOLUTION_TEST_SH);
  if (marker) write(join(d, 'sanitizer'), marker);
  return d;
}

// ---------------------------------------------------------------- cxxflags.sh
test('cxxflags: default sanitizers; the sanitizer file selects thread; a bad word is refused', () => {
  const d = tmp();
  const run = () => spawnSync('bash', [join(REPO, 'code/shared/cpp/cxxflags.sh'), d], { encoding: 'utf8' });
  let r = run();
  assert.equal(r.status, 0);
  assert.match(r.stdout, /-std=c\+\+23/);
  assert.match(r.stdout, /-fsanitize=address,undefined/);
  assert.doesNotMatch(r.stdout, /sanitize=thread/);
  write(join(d, 'sanitizer'), 'thread\n');
  r = run();
  assert.match(r.stdout, /-fsanitize=thread/);
  assert.doesNotMatch(r.stdout, /address/);
  write(join(d, 'sanitizer'), 'tsan\n');
  r = run();
  assert.equal(r.status, 2);
});

// ---------------------------------------------------------------- test_design.sh
const GO_LAB = `package x

func Double(n int) int { return n * 2 }
`;
const GO_LAB_TEST = (want) => `package x

import "testing"

func TestDouble(t *testing.T) {
	if got := Double(4); got != ${want} {
		t.Fatalf("Double(4) = %d; want ${want}", got)
	}
}
`;

test('test_design: clean tree with Go lab, claim program, C++ unit and pattern unit passes', () => {
  const root = tmp(); const code = codeRoot(root);
  write(join(code, 'H1.1', 'lab-x', 'x.go'), GO_LAB);
  write(join(code, 'H1.1', 'lab-x', 'x_test.go'), GO_LAB_TEST(8));
  write(join(code, 'H1.1', 'claim-1', 'main.go'), 'package main\n\nimport "fmt"\n\nfunc main() { fmt.Println("N=1: ok") }\n');
  write(join(code, 'H1.1', 'claim-1', 'expected.txt'), 'N=1: ok\n');
  cppUnit(code);
  const pu = join(code, 'L2.1', 'pat');
  const v = makeVariant(pu, 'plain', { 'a.txt': 'x = 1\n' }, [['01-b.patch', (w) => write(join(w, 'a.txt'), 'x = 1\ny = 2\n')]], '#!/usr/bin/env bash\ntrue\n');
  write(join(pu, 'unit.yaml'), 'kind: pattern\ndomain: demo\nvariants: [plain]\n');
  const table = sh('change_cost.sh', [v]).stdout;
  rmSync(join(pu, 'plain-work'), { recursive: true });
  write(join(pu, 'measured-plain.tsv'), table);

  let r = sh('test_design.sh', [code]);
  assert.equal(r.status, 0, r.stdout + r.stderr);
  assert.equal(r.stdout.trim(), 'All design code units passed');

  // a wrong expected.txt is reported
  write(join(code, 'H1.1', 'claim-1', 'expected.txt'), 'N=1: bad\n');
  r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /FAIL \(output differs from expected\.txt\): .*claim-1/);
  write(join(code, 'H1.1', 'claim-1', 'expected.txt'), 'N=1: ok\n');

  // a stale measured file is reported
  write(join(pu, 'measured-plain.tsv'), table.replace('base\tfiles=1', 'base\tfiles=9'));
  r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /measured-plain\.tsv is out of date/);
});

test('test_design: a broken Go lab prints the failing test name and message; gofmt violations fail', () => {
  const root = tmp(); const code = codeRoot(root);
  write(join(code, 'H1.1', 'lab-x', 'x.go'), GO_LAB);
  write(join(code, 'H1.1', 'lab-x', 'x_test.go'), GO_LAB_TEST(9));
  let r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /FAIL \(go vet \/ go test\)/);
  assert.match(r.stdout, /--- FAIL: TestDouble/);
  assert.match(r.stdout, /Double\(4\) = 8; want 9/);
  write(join(code, 'H1.1', 'lab-x', 'x_test.go'), GO_LAB_TEST(8));
  write(join(code, 'H1.1', 'lab-x', 'x.go'), 'package x\n\nfunc Double(n int) int {   return n*2 }\n');
  r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /FAIL \(gofmt\)/);
});

test('test_design: a Go package under shared/ is tested (a folder starting with _ would be skipped)', () => {
  const root = tmp(); const code = codeRoot(root);
  write(join(code, 'shared', 'go', 'p', 'p.go'), 'package p\n');
  write(join(code, 'shared', 'go', 'p', 'p_test.go'), 'package p\n\nimport "testing"\n\nfunc TestRuns(t *testing.T) { t.Fatal("ran") }\n');
  const r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /--- FAIL: TestRuns/);
});

test('test_design: a failing C++ check, a sanitizer finding and a compile warning all fail the unit', () => {
  let root = tmp(); let code = codeRoot(root);
  cppUnit(code, 'counter', PASSING + 'void wrong() { Counter c; c.add(1); CHECK(c.total() == 2); }\n', ['adds', 'wrong']);
  let r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /FAIL \(tests\): .*counter/);
  assert.match(r.stdout, /FAIL .*tests\.cpp:\d+: c\.total\(\) == 2/);

  root = tmp(); code = codeRoot(root);
  cppUnit(code, 'counter', 'void ub() { volatile int big = 2147483647; int next = big + 1; CHECK(next != 12345); }\n', ['ub']);
  r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /FAIL \(tests\)/);

  root = tmp(); code = codeRoot(root);
  cppUnit(code, 'counter', 'void w() { int unused; }\nvoid ok() { CHECK(true); }\n', ['w', 'ok']);
  r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
});

test('test_design: a pattern unit without variants fails', () => {
  const code = codeRoot(tmp());
  write(join(code, 'L1.1', 'p', 'unit.yaml'), 'kind: pattern\ndomain: demo\n');
  const r = sh('test_design.sh', [code]);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /MISSING variants/);
});

// ---------------------------------------------------------------- exercise_kit_check.sh
const BUCKET_REF = readFileSync(join(FIX, 'reference', 'bucket.go'), 'utf8');
function mutant(kind) {
  if (kind === 'm1') return BUCKET_REF.replace(/\tif b\.tokens > b\.burst \{\n\t\tb\.tokens = b\.burst\n\t\}\n/, '');
  if (kind === 'm2') return BUCKET_REF.replace('\tb.mu.Lock()\n\tdefer b.mu.Unlock()\n', '');
  if (kind === 'm3') return BUCKET_REF.replace('b.tokens += t.Sub(b.last).Seconds() * b.rate', 'b.tokens += float64(int(t.Sub(b.last).Seconds() * b.rate))');
  throw new Error(kind);
}
function bucketKit(root, kitPath = 'H5.6/lab/rung-1') {
  const ex = join(root, 'exercises'), ref = join(root, 'reference'), mut = join(root, 'reference-mutants');
  write(join(root, 'code', 'go.mod'), 'module selfengine/code\n\ngo 1.27\n');
  const k = join(ex, kitPath);
  write(join(k, 'test.sh'), readFileSync(join(FIX, 'test.sh'), 'utf8'));
  write(join(k, 'tests', 'bucket_test.go'), readFileSync(join(FIX, 'tests', 'bucket_test.go'), 'utf8'));
  write(join(k, 'starter', 'bucket.go'), readFileSync(join(FIX, 'starter', 'bucket.go'), 'utf8'));
  write(join(ref, kitPath, 'bucket.go'), BUCKET_REF);
  for (const m of ['m1', 'm2', 'm3']) write(join(mut, kitPath, m, 'bucket.go'), mutant(m));
  return { ex, ref, mut, k };
}
const kitCheck = (p, env = {}) => sh('exercise_kit_check.sh', [p.ex, p.ref, p.mut], { env: { ...process.env, ...env } });

test('exercise_kit_check: Go kit with three mutants (one caught only by the race detector) is consistent', () => {
  const root = tmp(); const p = bucketKit(root);
  const r = kitCheck(p);
  assert.equal(r.status, 0, r.stdout + r.stderr);
  assert.equal(r.stdout.trim(), 'All exercise kits consistent');
  // the m2 mutant passes the tests without -race, which is why the kit's test.sh must use it
  const m2 = join(p.mut, 'H5.6/lab/rung-1/m2');
  const plain = spawnSync('bash', ['-c', `cd "${root}" && mkdir -p w && cp "${m2}"/bucket.go "${p.k}"/tests/bucket_test.go w/ && cd w && printf 'module kit\\n\\ngo 1.27\\n' > go.mod && go test -count=1 .`], { encoding: 'utf8' });
  assert.equal(plain.status, 0, 'm2 should pass without -race');
});

test('exercise_kit_check: reports a failing reference, a passing starter, a passing mutant and too few mutants', () => {
  let root = tmp(); let p = bucketKit(root);
  write(join(p.ref, 'H5.6/lab/rung-1/bucket.go'), mutant('m1'));
  let r = kitCheck(p);
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /FAIL: reference does not pass: H5\.6\/lab\/rung-1/);

  root = tmp(); p = bucketKit(root);
  write(join(p.k, 'starter', 'bucket.go'), BUCKET_REF);
  r = kitCheck(p);
  assert.match(r.stdout, /FAIL: tests pass on the starter: H5\.6\/lab\/rung-1/);

  root = tmp(); p = bucketKit(root);
  write(join(p.mut, 'H5.6/lab/rung-1/m4/bucket.go'), BUCKET_REF);
  r = kitCheck(p);
  assert.match(r.stdout, /FAIL: tests pass on mutant H5\.6\/lab\/rung-1\/m4 \(tests too weak\)/);

  root = tmp(); p = bucketKit(root);
  rmSync(join(p.mut, 'H5.6/lab/rung-1/m3'), { recursive: true });
  r = kitCheck(p);
  assert.match(r.stdout, /FAIL: 2 mutants for H5\.6\/lab\/rung-1, need 3/);
  write(join(p.k, 'min_mutants'), '2\n');   // a ladder rung sets min_mutants to 2
  r = kitCheck(p);
  assert.equal(r.status, 0, r.stdout);
});

test('exercise_kit_check: C++ kit whose lock-free mutant is caught only by the thread sanitizer', () => {
  const root = tmp();
  const kit = join(root, 'exercises', 'L6.1', 'ex-1');
  const code = join(root, 'code');
  write(join(code, 'shared', 'cpp', 'check.hpp'), readFileSync(join(REPO, 'code/shared/cpp/check.hpp'), 'utf8'));
  write(join(code, 'shared', 'cpp', 'cxxflags.sh'), readFileSync(join(REPO, 'code/shared/cpp/cxxflags.sh'), 'utf8'));
  write(join(kit, 'test.sh'), readFileSync(join(REPO, 'templates/kit-cpp/test.sh'), 'utf8'));
  write(join(kit, 'sanitizer'), 'thread\n');
  write(join(kit, 'starter', 'counter.hpp'), '#pragma once\n#include <stdexcept>\nclass Counter { public: void add() { throw std::logic_error("not implemented"); } int total() const { throw std::logic_error("not implemented"); } };\n');
  write(join(kit, 'tests', 'tests.cpp'), `#include "check.hpp"
#include "counter.hpp"
#include <thread>
#include <vector>
void eight_threads() {
    Counter c;
    std::vector<std::thread> ts;
    for (int i = 0; i < 8; i++) ts.emplace_back([&c] { for (int j = 0; j < 1000; j++) c.add(); });
    for (auto& t : ts) t.join();
    CHECK(c.total() == 8000);
}
int main() { RUN(eight_threads); return check::report(); }
`);
  const ref = (body) => `#pragma once\n#include <atomic>\n#include <mutex>\nclass Counter {\npublic:\n${body}\n};\n`;
  write(join(root, 'reference/L6.1/ex-1/counter.hpp'), ref('    void add() { std::lock_guard<std::mutex> g(m_); ++n_; }\n    int total() const { return n_; }\nprivate:\n    std::mutex m_; int n_ = 0;'));
  // mutants: no lock (race); non-atomic increments with a volatile-free plain int; an off-by-one
  write(join(root, 'reference-mutants/L6.1/ex-1/nolock/counter.hpp'), ref('    void add() { ++n_; }\n    int total() const { return n_; }\nprivate:\n    int n_ = 0;'));
  write(join(root, 'reference-mutants/L6.1/ex-1/nolock2/counter.hpp'), ref('    void add() { n_ = n_ + 1; }\n    int total() const { return n_; }\nprivate:\n    int n_ = 0;'));
  write(join(root, 'reference-mutants/L6.1/ex-1/offbyone/counter.hpp'), ref('    void add() { std::lock_guard<std::mutex> g(m_); ++n_; }\n    int total() const { return n_ - 1; }\nprivate:\n    std::mutex m_; int n_ = 0;'));
  const r = sh('exercise_kit_check.sh', [join(root, 'exercises'), join(root, 'reference'), join(root, 'reference-mutants')]);
  assert.equal(r.status, 0, r.stdout + r.stderr);
});

test('exercise_kit_check: a needs_docker kit is skipped, or fails with REQUIRE_DOCKER=1, when Docker is not available', () => {
  const root = tmp(); const p = bucketKit(root);
  write(join(p.k, 'needs_docker'), '');
  // an empty PATH-less docker: run with a PATH that has bash and coreutils but no docker
  const bin = join(root, 'bin'); mkdirSync(bin);
  for (const t of ['bash', 'find', 'sort', 'dirname', 'cat', 'tr', 'mkdir', 'sed', 'go', 'rm', 'mktemp', 'cp', 'tar', 'cksum', 'cut', 'date']) {
    const w = spawnSync('bash', ['-c', `command -v ${t}`], { encoding: 'utf8' }).stdout.trim();
    if (w) spawnSync('ln', ['-s', w, join(bin, t)]);
  }
  let r = kitCheck(p, { PATH: bin });
  assert.equal(r.status, 0, r.stdout + r.stderr);
  assert.match(r.stdout, /SKIPPED \(Docker unavailable\): H5\.6\/lab\/rung-1/);
  r = kitCheck(p, { PATH: bin, REQUIRE_DOCKER: '1' });
  assert.notEqual(r.status, 0);
  assert.match(r.stdout, /FAIL: Docker unavailable for H5\.6\/lab\/rung-1/);
});

// ---------------------------------------------------------------- new_attempt.sh
test('new_attempt: copies the starter into work/, refuses to overwrite, and prints the test command', () => {
  const root = tmp();
  mkdirSync(join(root, 'scripts'));
  writeFileSync(join(root, 'scripts', 'new_attempt.sh'), readFileSync(join(SCRIPTS, 'new_attempt.sh')));
  write(join(root, 'exercises/H5.6/lab/rung-1/test.sh'), 'true\n');
  write(join(root, 'exercises/H5.6/lab/rung-1/starter/bucket.go'), 'package ratelimit\n');
  const run = (...a) => spawnSync('bash', [join(root, 'scripts', 'new_attempt.sh'), ...a], { encoding: 'utf8' });
  let r = run('H5.6/lab/rung-1');
  assert.equal(r.status, 0, r.stderr);
  assert.ok(existsSync(join(root, 'work/H5.6/lab/rung-1/bucket.go')));
  assert.match(r.stdout, /bash exercises\/H5\.6\/lab\/rung-1\/test\.sh work\/H5\.6\/lab\/rung-1/);
  r = run('H5.6/lab/rung-1');
  assert.notEqual(r.status, 0);
  assert.match(r.stderr, /already exists/);
  r = run('H9.9/lab/rung-1');
  assert.notEqual(r.status, 0);
  assert.match(r.stderr, /no such kit/);
});

// ---------------------------------------------------------------- labserver.sh (local mode, stand-in docker)
function labServer(extraEnv = {}) {
  const root = tmp();
  const repo = join(root, 'repo');
  mkdirSync(join(repo, 'scripts'), { recursive: true });
  writeFileSync(join(repo, 'scripts', 'labserver.sh'), readFileSync(join(SCRIPTS, 'labserver.sh')));
  write(join(repo, 'code', 'go.mod'), 'module selfengine/code\n\ngo 1.27\n');
  write(join(repo, 'labserver', 'stacks', 'postgres.yaml'), 'services: {}\n');
  write(join(repo, 'labserver', 'stacks', 'kafka.yaml'), 'services: {}\n');
  write(join(repo, 'src', 'a.txt'), 'new\n');
  const mirror = join(root, 'mirror');
  const bin = join(root, 'bin'); mkdirSync(bin);
  const calls = join(root, 'docker-calls.txt');
  // Stand-in docker: records the call; "ps -q" prints a container id only for projects listed in $RUNNING.
  writeFileSync(join(bin, 'docker'), `#!/usr/bin/env bash
echo "$*" >> "${calls}"
if [[ "$*" == *" ps -q"* ]]; then
  for p in $RUNNING; do [[ "$*" == *"-p se-$p "* ]] && echo abc123; done
fi
exit 0
`);
  chmodx(join(bin, 'docker'));
  writeFileSync(join(repo, '.env.labserver'), `LABSERVER_HOST=local\nLABSERVER_DIR=${mirror}\n`);
  const env = { ...process.env, PATH: `${bin}:${process.env.PATH}`, HOME: root, ...extraEnv };
  const run = (...a) => spawnSync('bash', [join(repo, 'scripts', 'labserver.sh'), ...a], { encoding: 'utf8', env });
  return { root, repo, mirror, calls, run, env };
}

test('labserver: sync and exec refuse a folder without the marker; init creates it', () => {
  const s = labServer();
  mkdirSync(s.mirror); write(join(s.mirror, 'precious.txt'), 'keep\n');
  let r = s.run('sync');
  assert.notEqual(r.status, 0);
  assert.match(r.stderr, /refusing: .* has no \.labserver-mirror/);
  assert.ok(existsSync(join(s.mirror, 'precious.txt')));
  r = s.run('exec', 'true');
  assert.notEqual(r.status, 0);
  r = s.run('init');   // non-empty and not a mirror
  assert.notEqual(r.status, 0);
  assert.match(r.stderr, /not empty, and is not a mirror/);
  assert.equal(readFileSync(join(s.mirror, 'precious.txt'), 'utf8'), 'keep\n');
});

test('labserver: init refuses /, /home, the home folder and a parent of home', () => {
  for (const dir of ['/', '/home', '/usr/lib']) {
    const s = labServer();
    writeFileSync(join(s.repo, '.env.labserver'), `LABSERVER_HOST=local\nLABSERVER_DIR=${dir}\n`);
    const r = s.run('init');
    assert.notEqual(r.status, 0, dir);
    assert.match(r.stderr, /refusing/);
  }
  const s = labServer();
  writeFileSync(join(s.repo, '.env.labserver'), `LABSERVER_HOST=local\nLABSERVER_DIR=${s.root}\n`);   // HOME is s.root
  assert.notEqual(s.run('init').status, 0);
  writeFileSync(join(s.repo, '.env.labserver'), `LABSERVER_HOST=local\nLABSERVER_DIR=${dirOf(s.root)}\n`);  // parent of home
  assert.notEqual(s.run('init').status, 0);
});
const dirOf = (p) => resolve(p, '..');

test('labserver: after sync a stale file is gone and a results file three folders deep is kept', () => {
  const s = labServer();
  assert.equal(s.run('init').status, 0);
  write(join(s.mirror, 'stale.txt'), 'old\n');
  write(join(s.mirror, 'code/H0.4/lab-q/experiments/sweep/results/2026-10-21-labserver.txt'), 'kept\n');
  write(join(s.repo, 'code/H0.4/lab-q/experiments/sweep/results/local.txt'), 'must not overwrite or duplicate\n');
  const r = s.run('sync');
  assert.equal(r.status, 0, r.stderr);
  assert.ok(!existsSync(join(s.mirror, 'stale.txt')));
  assert.equal(readFileSync(join(s.mirror, 'src/a.txt'), 'utf8'), 'new\n');
  assert.equal(readFileSync(join(s.mirror, 'code/H0.4/lab-q/experiments/sweep/results/2026-10-21-labserver.txt'), 'utf8'), 'kept\n');
  assert.ok(existsSync(join(s.mirror, '.labserver-mirror')));
});

test('labserver: integration starts only stacks that are not running, and stops only those; failure still stops them', () => {
  const s = labServer({ RUNNING: 'postgres' });
  assert.equal(s.run('init').status, 0);
  // the mirror needs a runnable `go test`: a package with one passing test
  write(join(s.repo, 'code/H1.1/lab-x/x.go'), 'package x\n');
  write(join(s.repo, 'code/H1.1/lab-x/x_test.go'), '//go:build integration\n\npackage x\n\nimport "testing"\n\nfunc TestInt(t *testing.T) {}\n');
  let r = s.run('integration', 'postgres', 'kafka', '--', './H1.1/...');
  assert.equal(r.status, 0, r.stdout + r.stderr);
  const calls = readFileSync(s.calls, 'utf8');
  assert.match(calls, /-p se-kafka .*up -d --wait/);
  assert.match(calls, /-p se-kafka .*down -v/);
  assert.doesNotMatch(calls, /-p se-postgres .*up -d/);
  assert.doesNotMatch(calls, /-p se-postgres .*down/);

  // a failing integration test returns non-zero and still stops the started stack
  write(join(s.repo, 'code/H1.1/lab-x/x_test.go'), '//go:build integration\n\npackage x\n\nimport "testing"\n\nfunc TestInt(t *testing.T) { t.Fatal("boom") }\n');
  rmSync(s.calls);
  r = s.run('integration', 'kafka', '--', './H1.1/...');
  assert.notEqual(r.status, 0);
  assert.match(readFileSync(s.calls, 'utf8'), /-p se-kafka .*down -v/);
});

// ---------------------------------------------------------------- new_kit.mjs
test('new_kit: creates a Go kit from the template; rung 2 starts from rung 1 reference; refuses to overwrite', () => {
  const root = tmp();
  mkdirSync(join(root, 'scripts'));
  writeFileSync(join(root, 'scripts', 'new_kit.mjs'), readFileSync(join(SCRIPTS, 'new_kit.mjs')));
  cpSync(join(REPO, 'templates'), join(root, 'templates'), { recursive: true });
  const run = (...a) => spawnSync('node', [join(root, 'scripts', 'new_kit.mjs'), ...a], { encoding: 'utf8' });
  let r = run('H5.6/lab/rung-1', '--lang', 'go', '--package', 'ratelimit', '--title', 'Token bucket');
  assert.equal(r.status, 0, r.stderr);
  const k = join(root, 'exercises/H5.6/lab/rung-1');
  assert.ok(existsSync(join(k, 'starter/ratelimit.go')));
  assert.ok(existsSync(join(k, 'tests/ratelimit_test.go')));
  assert.match(readFileSync(join(k, 'README.md'), 'utf8'), /# H5\.6\/lab\/rung-1: Token bucket/);
  assert.ok(existsSync(join(root, 'reference-mutants/H5.6/lab/rung-1')));
  r = run('H5.6/lab/rung-1', '--lang', 'go', '--package', 'ratelimit');
  assert.notEqual(r.status, 0);
  // rung 2 needs the rung 1 reference to be non-empty
  r = run('H5.6/lab/rung-2', '--lang', 'go', '--package', 'ratelimit');
  assert.notEqual(r.status, 0);
  assert.match(r.stderr, /previous rung's reference is missing or empty/);
  write(join(root, 'reference/H5.6/lab/rung-1/ratelimit.go'), 'package ratelimit\n// ref\n');
  r = run('H5.6/lab/rung-2', '--lang', 'go', '--package', 'ratelimit');
  assert.equal(r.status, 0, r.stderr);
  assert.match(readFileSync(join(root, 'exercises/H5.6/lab/rung-2/starter/ratelimit.go'), 'utf8'), /ref/);
  assert.equal(readFileSync(join(root, 'exercises/H5.6/lab/rung-2/min_mutants'), 'utf8').trim(), '2');
});
