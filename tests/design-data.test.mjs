import { test } from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { parse } from 'yaml';
import { rubricsFile, constantsFile, designConfig } from '../src/lib/schemas.mjs';
import { validateRubrics, validateConstants } from '../src/lib/validate-design.mjs';
import { exportConstants } from '../scripts/constants_export.mjs';

const load = (f) => parse(readFileSync(new URL(`../src/data/${f}`, import.meta.url), 'utf8'));
const has = (errs, re) => assert.ok(errs.some((e) => re.test(e)), errs.join('\n'));

test('the real rubrics, config and constants are valid', () => {
  const rubrics = rubricsFile.parse(load('rubrics.yaml'));
  assert.deepEqual(validateRubrics(rubrics), []);
  designConfig.parse(load('design.config.yaml'));
  assert.deepEqual(validateConstants(constantsFile.parse(load('constants.yaml'))), []);
});
test('rubric weights, critical criteria, judgement words and missing standards are caught', () => {
  const r = structuredClone(rubricsFile.parse(load('rubrics.yaml')));
  r[0].criteria[0].weight = 11;
  has(validateRubrics(r), /rubric-lld-build-v1 weights sum to 101/);
  r[0].criteria[0].weight = 10;
  r[1].criteria.forEach((c) => (c.critical = false));
  has(validateRubrics(r), /rubric-hld-mock-v1 has no critical criterion/);
  r[2].criteria[0].anchors[2] = 'Good questions';
  has(validateRubrics(r), /judgement word/);
  has(validateRubrics(r.slice(0, 3)), /missing standard rubric rubric-hld-failure-v1/);
});
test('a rubric with a missing anchor fails the schema', () => {
  const r = structuredClone(load('rubrics.yaml'));
  delete r[0].criteria[0].anchors[1];
  assert.equal(rubricsFile.safeParse(r).success, false);
});
const C = { id: 'ssd-random-read', quantity: 'SSD random read latency', value: 1e-4, unit: 's', display: 'about 100 microseconds',
  source: { title: 'T', url: 'https://example.com/x', accessed: '2026-10-14', section: 's' }, caveat: 'c' };
test('constants: schema, duplicates, future dates and export', () => {
  assert.equal(constantsFile.safeParse([C]).success, true);
  assert.equal(constantsFile.safeParse([{ ...C, source: { ...C.source, url: 'nope' } }]).success, false);
  assert.equal(constantsFile.safeParse([{ ...C, caveat: undefined }]).success, false);
  has(validateConstants([C, C]), /duplicate constant id/);
  has(validateConstants([C], '2026-01-01'), /in the future/);
  has(validateConstants([{ ...C, value: 0 }]), /positive finite/);
  const text = 'ssd-random-read:\n';
  assert.throws(() => exportConstants(text));
  const out = JSON.parse(exportConstants(`- id: b\n  quantity: q\n  value: 2\n  unit: bytes\n  display: d\n  source: {title: t, url: "https://x.y", accessed: 2026-10-14, section: s}\n  caveat: c\n- id: a\n  quantity: q\n  value: 1\n  unit: s\n  display: d\n  source: {title: t, url: "https://x.y", accessed: 2026-10-14, section: s}\n  caveat: c\n`));
  assert.deepEqual(Object.keys(out), ['a', 'b']);
  assert.deepEqual(out.a, { value: 1, unit: 's' });
});
