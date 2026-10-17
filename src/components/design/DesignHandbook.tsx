// Pattern Handbook (LLD) and Component Handbook (HLD) (Section 11.5): by symptom or need, by topic, "as of topic X", flashcards.
// HLD entries link the lab test that shows the guarantee holding and breaking.
import { useEffect, useState } from 'react';
import { getCurrentTopic } from '../../lib/storage';

export type HCard = { topic: string; order: number; id: string; name: string; property: string; test: string; cost: string; href: string | null; holds?: string; breaks?: string };
export type HGroup = { signal: string; choose: string; chooseName: string; when: string; topic: string; order: number; over: string[] };

export default function DesignHandbook({ track, topics, cards, groups }: { track: 'lld' | 'hld'; topics: { id: string; order: number; title: string }[]; cards: HCard[]; groups: HGroup[] }) {
  const [asOf, setAsOf] = useState(topics.at(-1)?.order ?? 1);
  const [mode, setMode] = useState<'signal' | 'topic' | 'flash'>('signal');
  const [i, setI] = useState(0);
  const [flipped, setFlipped] = useState(false);
  useEffect(() => { const cur = getCurrentTopic(track); const t = topics.find((x) => x.id === cur); if (t) setAsOf(t.order); }, []);
  const vis = cards.filter((c) => c.order <= asOf);
  const g = groups.filter((x) => x.order <= asOf);
  const flash = vis[i % Math.max(vis.length, 1)];
  const label = track === 'lld' ? 'symptom' : 'need';
  return (
    <div className="design-handbook">
      <label>As of topic{' '}
        <select value={asOf} onChange={(e) => setAsOf(Number(e.target.value))}>{topics.map((t) => <option key={t.id} value={t.order}>{t.id} {t.title.slice(0, 50)}</option>)}</select>
      </label>
      <p role="tablist">
        {(['signal', 'topic', 'flash'] as const).map((m) => <button key={m} type="button" className={mode === m ? '' : 'secondary'} onClick={() => setMode(m)}>{m === 'signal' ? `By ${label}` : m === 'topic' ? 'By topic' : 'Flashcards'}</button>)}
      </p>
      {mode === 'signal' && (g.length === 0 ? <p className="muted">No entries yet.</p> : (
        <ul>{g.map((x, k) => <li key={k}><strong>{x.signal}</strong>: choose <a href={`#card-${x.choose}`}>{x.chooseName}</a> when {x.when}{x.over.length ? `. Instead of: ${x.over.join('; ')}` : ''}</li>)}</ul>
      ))}
      {mode === 'topic' && (vis.length === 0 ? <p className="muted">No cards yet.</p> : topics.filter((t) => t.order <= asOf).map((t) => {
        const cs = vis.filter((c) => c.topic === t.id);
        return cs.length > 0 && (
          <section key={t.id}><h3>{t.id} {t.title}</h3>{cs.map((c) => (
            <div key={c.id} id={`card-${c.id}`}>
              <p><strong>{c.href ? <a href={c.href}>{c.name}</a> : c.name}</strong>: {c.property}</p>
              <p className="muted">Test: {c.test} Cost: {c.cost}{c.holds ? ` Lab: holds in ${c.holds}, breaks in ${c.breaks}.` : ''}</p>
            </div>
          ))}</section>
        );
      }))}
      {mode === 'flash' && (flash ? (
        <div>
          <p><strong>{flash.name}</strong> ({flash.topic})</p>
          {!flipped ? <button type="button" onClick={() => setFlipped(true)}>What property decides it?</button> : <><p>{flash.property}</p><p>Test: {flash.test}</p><button type="button" onClick={() => { setFlipped(false); setI(i + 1); }}>Next</button></>}
        </div>
      ) : <p className="muted">No cards yet.</p>)}
    </div>
  );
}
