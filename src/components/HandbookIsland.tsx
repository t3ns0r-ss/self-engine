import { useEffect, useMemo, useState } from 'react';
import { getSettings } from '../lib/storage';

export type HCard = {
  topic: string; order: number; href: string; id: string; name: string; property: string; theorem: string;
  weak: string[]; kill: string[]; sample: string | null;
};
export type HGroup = { signal: string; entries: { topic: string; order: number; choose: string; when: string; over: { card: string; because: string }[] }[] };

export default function HandbookIsland({ topics, cards, groups }: { topics: { id: string; order: number; title: string }[]; cards: HCard[]; groups: HGroup[] }) {
  const [asOf, setAsOf] = useState(topics.at(-1)!.order);
  const [mode, setMode] = useState<'signal' | 'topic' | 'flash'>('signal');
  const [flashIndex, setFlashIndex] = useState(0);
  const [flipped, setFlipped] = useState(false);
  useEffect(() => {
    const cur = getSettings().currentTopic;
    const t = topics.find((x) => x.id === cur);
    if (t) setAsOf(t.order);
  }, []);

  const visibleCards = cards.filter((c) => c.order <= asOf);
  const visibleGroups = groups
    .map((g) => ({ ...g, entries: g.entries.filter((e) => e.order <= asOf) }))
    .filter((g) => g.entries.length);
  const deck = useMemo(() => {
    const d = [...visibleCards];
    for (let i = d.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [d[i], d[j]] = [d[j], d[i]];
    }
    return d;
  }, [asOf, mode]);
  const card = deck[flashIndex % Math.max(1, deck.length)];

  return (
    <div className="handbook">
      <div className="filters">
        <label>
          As of topic{' '}
          <select value={asOf} onChange={(e) => { setAsOf(Number(e.target.value)); setFlashIndex(0); setFlipped(false); }}>
            {topics.map((t) => <option key={t.id} value={t.order}>{t.id} {t.title}</option>)}
          </select>
        </label>{' '}
        <span role="group" aria-label="View">
          {(['signal', 'topic', 'flash'] as const).map((m) => (
            <button key={m} type="button" className={mode === m ? '' : 'secondary'} aria-pressed={mode === m} onClick={() => setMode(m)}>
              {m === 'signal' ? 'By weak signal' : m === 'topic' ? 'By topic' : 'Flashcards'}
            </button>
          ))}
        </span>
      </div>

      {mode === 'signal' && visibleGroups.map((g) => (
        <section key={g.signal}>
          <h3>{g.signal}</h3>
          <ul>
            {g.entries.map((e, i) => (
              <li key={i}>
                <strong>{e.choose}</strong> ({e.topic}) when {e.when.replace(/\.$/, '')}.
                {e.over.length > 0 && <ul>{e.over.map((o, k) => <li key={k}>over {o.card}: {o.because}</li>)}</ul>}
              </li>
            ))}
          </ul>
        </section>
      ))}

      {mode === 'topic' && visibleCards.map((c) => (
        <section key={`${c.topic}:${c.id}`} className="recognition-card">
          <h3><a href={c.href}>{c.name}</a> <span className="muted">({c.topic})</span></h3>
          <p><strong>Decisive property</strong> ({c.theorem}): {c.property}</p>
          <p><strong>Weak signals:</strong> {c.weak.join('; ')}</p>
          <p><strong>Kill signals:</strong> {c.kill.join('; ')}</p>
        </section>
      ))}

      {mode === 'flash' && card && (
        <section className="recognition-card flashcard">
          {!flipped ? (
            <>
              <p><strong>Weak signals:</strong> {card.weak.join('; ')}</p>
              {card.sample && <p><strong>Example problem:</strong> {card.sample}</p>}
              <p className="muted">Which card, and what property would you check?</p>
              <button type="button" onClick={() => setFlipped(true)}>Show the card</button>
            </>
          ) : (
            <>
              <h3>{card.name} <span className="muted">({card.topic})</span></h3>
              <p><strong>Decisive property:</strong> {card.property}</p>
              <button type="button" onClick={() => { setFlipped(false); setFlashIndex(flashIndex + 1); }}>Next card</button>
            </>
          )}
          <p className="muted">Card {(flashIndex % deck.length) + 1} of {deck.length}</p>
        </section>
      )}
    </div>
  );
}
