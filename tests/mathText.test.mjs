import test from 'node:test';
import assert from 'node:assert/strict';
import { mathText } from '../src/lib/mathText.ts';
import { normalise } from '../scripts/check_numbers.mjs';
import { checkMdx, checkYaml } from '../scripts/check_math.mjs';

test('mathText renders inline and display maths and escapes the rest', () => {
  const h = mathText('Cost is $O(n \\log n)$ and a < b & `x[i]`.');
  assert.match(h, /class="katex"/);
  assert.match(h, /a &lt; b &amp; <code>x\[i\]<\/code>/);
  assert.match(mathText('$$x^2$$'), /katex-display/);
});
test('mathText keeps escaped and lone dollars as text and never throws', () => {
  assert.equal(mathText('it costs \\$5 and \\$6'), 'it costs $5 and $6');
  assert.equal(mathText('a lone $ sign'), 'a lone $ sign');
  assert.doesNotThrow(() => mathText('$\\badmacro{$'));
});
test('check_numbers normalise matches formatted numbers', () => {
  const nums = (t) => normalise(t).match(/\d+(?:\.\d+)?/g);
  assert.deepEqual(nums('2·10^5'), nums('$2 \\cdot 10^{5}$').map((x) => x));
});
test('check_math flags plain maths and accepts formatted maths', () => {
  assert.equal(checkMdx('Cost O(n log n) here').length, 1);
  assert.equal(checkMdx('Cost $O(n \\log n)$ here and `a^b` code').length, 0);
  assert.equal(checkMdx('## Heading with O(n)\n').length, 0);
  assert.equal(checkYaml('summary:\n  - "ok $n \\\\le 5$ and 10^5 bad"\n').length, 1);
});
