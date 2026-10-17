// "Ask first" box (Section 11.2): type the questions you would ask, reveal the clarifying list, tick the critical ones you asked.
import { useState } from 'react';

export type Clarifying = { q: string; a: string; critical: boolean };

export default function AskFirst({ clarifying }: { clarifying: Clarifying[] }) {
  const [text, setText] = useState('');
  const [revealed, setRevealed] = useState(false);
  const [asked, setAsked] = useState<Set<number>>(new Set());
  const critical = clarifying.map((c, i) => [c, i] as const).filter(([c]) => c.critical);
  const hit = critical.filter(([, i]) => asked.has(i)).length;
  return (
    <div className="ask-first">
      <label htmlFor="ask-first-text"><strong>Ask first.</strong> Write the questions you would ask before designing (one per line).</label>
      <textarea id="ask-first-text" rows={4} value={text} disabled={revealed} onChange={(e) => setText(e.target.value)} />
      {!revealed ? (
        <button type="button" disabled={text.trim().length === 0} onClick={() => setRevealed(true)}>Reveal the clarifying questions</button>
      ) : (
        <>
          <p>Tick the critical questions you asked: {hit} of {critical.length}.</p>
          <ul>
            {clarifying.map((c, i) => (
              <li key={i}>
                <label>
                  <input type="checkbox" checked={asked.has(i)} onChange={() => setAsked((s) => { const n = new Set(s); n.has(i) ? n.delete(i) : n.add(i); return n; })} />{' '}
                  {c.critical && <strong>(critical) </strong>}{c.q}
                </label>
                <br /><span className="muted">Answer: {c.a}</span>
              </li>
            ))}
          </ul>
        </>
      )}
    </div>
  );
}
