// Markdown of an attempt and its rubric, copied to the clipboard for a second reading (Section 11.2).
// Fallback when the clipboard is blocked: the same text in a selectable box.
import { useState } from 'react';
import { getDesignAttempts } from '../../lib/storage';
import type { Rubric } from './RubricScorer';

export default function ExportForReview({ globalId, prompt, rubric }: { globalId: string; prompt: string; rubric?: Rubric }) {
  const [text, setText] = useState('');
  const [copied, setCopied] = useState(false);
  const build = () => {
    const a = (getDesignAttempts()[globalId] ?? []).at(-1);
    const lines = [`# ${globalId}`, '', prompt, '', '## My attempt', a ? `Date: ${a.date}; minutes: ${a.minutes ?? '?'}; hints: ${a.hints ?? 0}` : 'No attempt logged.'];
    if (rubric && a?.scores) {
      lines.push('', `## Rubric ${rubric.id}`);
      for (const c of rubric.criteria) lines.push(`- ${c.name}: ${a.scores[c.id]?.score ?? '-'} / 2. ${a.scores[c.id]?.evidence ?? ''}`);
    }
    if (a?.note) lines.push('', '## Notes', a.note);
    return lines.join('\n');
  };
  return (
    <div className="export-for-review">
      <button type="button" onClick={async () => { const t = build(); setText(t); try { await navigator.clipboard.writeText(t); setCopied(true); } catch { setCopied(false); } }}>Copy for review</button>
      {copied && <span> Copied.</span>}
      {text && !copied && <textarea readOnly rows={8} value={text} onFocus={(e) => e.currentTarget.select()} />}
    </div>
  );
}
