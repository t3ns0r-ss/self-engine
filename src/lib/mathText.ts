// Renders a plain string from a data file (YAML text) to safe HTML: `$...$` and `$$...$$` become KaTeX maths,
// `...` becomes inline code, `\$` is a literal dollar sign, and everything else is HTML-escaped.
// LESSON_RESTORE_PLAN.md Phase 0, step 4.
import katex from 'katex';

const esc = (s: string) => s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;');

function plain(s: string): string {
  // inline code first, then the escaped dollar
  return s.split(/(`[^`\n]+`)/).map((part) =>
    part.length > 2 && part[0] === '`' && part.endsWith('`') ? `<code>${esc(part.slice(1, -1))}</code>` : esc(part).replace(/\\\$/g, '$'),
  ).join('');
}

function tex(src: string, display: boolean): string {
  return katex.renderToString(src, { displayMode: display, throwOnError: false, output: 'htmlAndMathml' });
}

export function mathText(input: string | null | undefined): string {
  const s = input ?? '';
  if (!s.includes('$') && !s.includes('`')) return esc(s);
  let out = '';
  let i = 0;
  let buf = '';
  while (i < s.length) {
    const c = s[i];
    if (c === '\\' && s[i + 1] === '$') { buf += '\\$'; i += 2; continue; }
    if (c === '$') {
      const display = s[i + 1] === '$';
      const open = display ? 2 : 1;
      let j = i + open;
      let end = -1;
      while (j < s.length) {
        if (s[j] === '\\') { j += 2; continue; }
        if (s[j] === '$' && (!display || s[j + 1] === '$')) { end = j; break; }
        j++;
      }
      if (end > i + open - 0 && end !== -1) {
        out += plain(buf); buf = '';
        out += tex(s.slice(i + open, end), display);
        i = end + open;
        continue;
      }
    }
    buf += c; i++;
  }
  return out + plain(buf);
}
