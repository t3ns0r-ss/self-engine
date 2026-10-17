// Recognition drill for the design tracks (Section 8.10). Items are reserved: fetched in the browser from
// /data/reserved/{topic}.json, never present in built HTML. "None" is an answer; a one-sentence property is required before reveal.
import { useEffect, useState } from 'react';
import { fetchCards, fetchReserved, type CardOption, type ReservedItem } from '../lib/design-client';
import { addDesignAttempt, getDrills, saveDrill, today } from '../lib/storage';
import { useStore } from '../lib/useStore';

const NONE = '__none__';

function Item({ item, options }: { item: ReservedItem; options: CardOption[] }) {
  const state = useStore(() => getDrills()[item.globalId], undefined);
  const [choice, setChoice] = useState('');
  const [property, setProperty] = useState('');
  const [shownAt] = useState(() => Date.now());
  const revealed = !!state?.revealed;
  const a = item.answer;
  const right = revealed && a && (a.kind === 'none' ? state?.chosenCard === NONE : state?.chosenCard === `${a.card.topic}/${a.card.card}`);
  return (
    <li className={revealed ? (right ? 'drill-right' : 'drill-wrong') : undefined}>
      <p>{item.prompt}</p>
      <label htmlFor={`d-${item.id}-c`}>Structure or component</label>
      <select id={`d-${item.id}-c`} value={revealed ? state?.chosenCard ?? '' : choice} disabled={revealed} onChange={(e) => setChoice(e.target.value)}>
        <option value="">Choose…</option>
        <option value={NONE}>None: the simplest thing is enough</option>
        {options.map((o) => <option key={`${o.topic}/${o.card}`} value={`${o.topic}/${o.card}`}>{o.name} ({o.topic})</option>)}
      </select>
      <label htmlFor={`d-${item.id}-p`}>The property you checked, in one sentence</label>
      <input id={`d-${item.id}-p`} value={revealed ? state?.property ?? '' : property} disabled={revealed} onChange={(e) => setProperty(e.target.value)} />
      {!revealed ? (
        <button type="button" disabled={!choice || property.trim().length < 8} onClick={() => {
          saveDrill(item.globalId, { chosenCard: choice, property: property.trim(), revealed: true });
          const ok = a ? (a.kind === 'none' ? choice === NONE : choice === `${a.card.topic}/${a.card.card}`) : false;
          addDesignAttempt(item.globalId, { date: today(), minutes: Math.round((Date.now() - shownAt) / 60000), testsPassed: ok });
        }}>Reveal</button>
      ) : a && (
        <div className="drill-answer">
          <p><strong>{right ? 'Right.' : 'Not this time.'}</strong> {a.kind === 'none' ? `Answer: none. Simplest: ${a.simplest}. ${a.why}` : `Answer: ${options.find((o) => o.topic === a.card.topic && o.card === a.card.card)?.name ?? a.card.card}.`}</p>
          {a.kind === 'card' && <><p><strong>Property:</strong> {a.property}</p><p><strong>Why other structures fail:</strong> {a.why_others_fail}</p></>}
          <button type="button" className="secondary" onClick={() => saveDrill(item.globalId, { revealed: false, chosenCard: '', property: '' })}>Try again later</button>
        </div>
      )}
    </li>
  );
}

export default function Drill({ topic }: { topic: string }) {
  const [items, setItems] = useState<ReservedItem[] | null>(null);
  const [options, setOptions] = useState<CardOption[]>([]);
  const [err, setErr] = useState('');
  const track = topic.startsWith('L') ? 'lld' : 'hld';
  useEffect(() => {
    fetchReserved(topic).then((all) => setItems(all.filter((e) => e.role === 'drill'))).catch((e) => setErr(e.message));
    fetchCards(track).then(setOptions).catch(() => setOptions([]));
  }, [topic]);
  if (err) return <p className="notice">Could not load the drill: {err}</p>;
  if (!items) return <p>Loading…</p>;
  if (!items.length) return <p className="muted">No drill items yet.</p>;
  return (
    <div className="drill">
      <p>Choose the structure (or "none"), write the property that decides it, then reveal.</p>
      <ol>{items.map((i) => <Item key={i.globalId} item={i} options={options.filter((o) => o.order <= (options.find((x) => x.topic === topic)?.order ?? 1e9))} />)}</ol>
    </div>
  );
}
