import { useRef, useState } from 'react';
import { MISTAKE_LABELS, exportAll, getProblems, importAll, resetAll, today, type Mistake } from '../lib/storage';

type Info = { title: string; topic: string; card: string };

/** Markdown in the FEEDBACK.md format (PLAN.md Section 16.3), one item per topic and card. */
export function feedbackMarkdown(problems: Record<string, Info>): string {
  const groups = new Map<string, { topic: string; card: string; items: { id: string; mistake: Mistake; note?: string }[] }>();
  for (const [id, log] of Object.entries(getProblems())) {
    if (!log.mistake) continue;
    const info = problems[id] ?? { title: id, topic: '?', card: '?' };
    const key = `${info.topic}|${info.card}`;
    const g = groups.get(key) ?? { topic: info.topic, card: info.card, items: [] };
    g.items.push({ id, mistake: log.mistake, note: log.note });
    groups.set(key, g);
  }
  if (!groups.size) return '';
  return [...groups.values()]
    .sort((a, b) => a.topic.localeCompare(b.topic) || a.card.localeCompare(b.card))
    .map((g) => {
      const counts = new Map<string, number>();
      for (const it of g.items) counts.set(it.mistake, (counts.get(it.mistake) ?? 0) + 1);
      const what = [...counts].map(([m, n]) => `${n} × ${MISTAKE_LABELS[m as Exclude<Mistake, ''>]}`).join(', ');
      const notes = g.items.filter((i) => i.note).map((i) => `${i.id}: ${i.note!.replace(/\s+/g, ' ')}`).join('; ');
      return [
        `## ${today()} — topic ${g.topic}`,
        `- Type: ${counts.has('recognition') ? 'confusing' : 'other'}`,
        `- Where: card ${g.card} (problems ${g.items.map((i) => i.id).join(', ')})`,
        `- What: ${what}.${notes ? ` Notes: ${notes}` : ''}`,
        '- Status: open',
      ].join('\n');
    })
    .join('\n\n') + '\n';
}

export default function ProgressIsland({ problems }: { problems: Record<string, Info> }) {
  const [msg, setMsg] = useState('');
  const [feedback, setFeedback] = useState<string | null>(null);
  const fileRef = useRef<HTMLInputElement>(null);

  function download() {
    const blob = new Blob([JSON.stringify(exportAll(), null, 2)], { type: 'application/json' });
    const a = document.createElement('a');
    a.href = URL.createObjectURL(blob);
    a.download = `cp-progress-${today()}.json`;
    a.click();
    URL.revokeObjectURL(a.href);
    setMsg('Exported.');
  }
  async function upload(file: File) {
    let data: unknown;
    try {
      data = JSON.parse(await file.text());
    } catch {
      setMsg('That file is not valid JSON.');
      return;
    }
    if (!confirm('Importing replaces all progress in this browser. Continue?')) return;
    const err = importAll(data);
    setMsg(err ?? 'Imported.');
  }
  async function copyFeedback() {
    const md = feedbackMarkdown(problems);
    if (!md) {
      setFeedback(null);
      setMsg('No mistakes logged yet, so there is nothing to send.');
      return;
    }
    setFeedback(md);
    try {
      await navigator.clipboard.writeText(md);
      setMsg('Copied. Paste it at the end of FEEDBACK.md.');
    } catch {
      // The Clipboard API needs HTTPS or localhost; fall back to a selectable box.
      setMsg('Could not copy automatically. Select the text below and copy it.');
    }
  }

  return (
    <div>
      <h2 id="export">Export and import</h2>
      <div className="log-actions">
        <button type="button" onClick={download}>Export progress</button>
        <button type="button" className="secondary" onClick={() => fileRef.current?.click()}>Import from file…</button>
        <input ref={fileRef} type="file" accept="application/json,.json" hidden onChange={(e) => { const f = e.target.files?.[0]; if (f) upload(f); e.target.value = ''; }} />
      </div>
      <h2 id="feedback">Send feedback</h2>
      <p>Builds a note from your logged mistakes, grouped by topic and card, in the format of <code>FEEDBACK.md</code>.</p>
      <button type="button" onClick={copyFeedback}>Copy feedback</button>
      {feedback && <textarea className="feedback-box" readOnly rows={10} value={feedback} onFocus={(e) => e.target.select()} />}
      <h2 id="reset">Reset</h2>
      <button type="button" className="secondary" onClick={() => {
        if (confirm('Delete all progress in this browser? Export first if you might want it back.')) setMsg(resetAll() ? 'All progress deleted.' : 'Browser storage is unavailable.');
      }}>Reset all progress</button>
      <p role="status">{msg}</p>
    </div>
  );
}
