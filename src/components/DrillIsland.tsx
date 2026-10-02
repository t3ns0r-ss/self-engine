import { useState } from 'react';
import { getDrills, saveDrill, type DrillState } from '../lib/storage';
import { useStore } from '../lib/useStore';
import PlatformBadge from './PlatformBadge';

export type DrillItem = {
  id: string; title: string; url: string; source: string; difficulty: string; summary: string;
  answer: string; answerName: string; property: string; why: string;
};
export type CardOption = { value: string; label: string };

function Item({ item, state, options }: { item: DrillItem; state?: DrillState; options: CardOption[] }) {
  const [choice, setChoice] = useState(state?.chosenCard ?? '');
  const [property, setProperty] = useState(state?.property ?? '');
  const revealed = !!state?.revealed;
  const chosen = revealed ? state?.chosenCard ?? '' : choice;
  const right = revealed && state?.chosenCard === item.answer;
  return (
    <li className={revealed ? (right ? 'drill-right' : 'drill-wrong') : undefined}>
      <p>
        <a href={item.url} target="_blank" rel="noopener noreferrer">{item.title}</a> <PlatformBadge source={item.source} />{' '}
        <span className="muted">{item.difficulty}</span>
      </p>
      <p>{item.summary}</p>
      <label htmlFor={`drill-${item.id}-card`}>Tool</label>
      <select id={`drill-${item.id}-card`} value={chosen} disabled={revealed} onChange={(e) => setChoice(e.target.value)}>
        <option value="">Choose a card…</option>
        {options.map((o) => <option key={o.value} value={o.value}>{o.label}</option>)}
      </select>
      <label htmlFor={`drill-${item.id}-prop`}>Property you verified</label>
      <input id={`drill-${item.id}-prop`} value={revealed ? state?.property ?? '' : property} disabled={revealed} onChange={(e) => setProperty(e.target.value)} />
      {!revealed ? (
        <button type="button" disabled={!choice} onClick={() => saveDrill(item.id, { chosenCard: choice, property: property.trim(), revealed: true })}>
          Reveal
        </button>
      ) : (
        <div className="drill-answer">
          <p><strong>{right ? 'Right.' : 'Not this time.'}</strong> Answer: {item.answerName}</p>
          <p><strong>Property:</strong> {item.property}</p>
          <p><strong>Why other tools fail:</strong> {item.why}</p>
          <button type="button" className="secondary" onClick={() => { setChoice(''); setProperty(''); saveDrill(item.id, { revealed: false, chosenCard: '', property: '' }); }}>
            Try again later
          </button>
        </div>
      )}
    </li>
  );
}

export default function DrillIsland({ items, options }: { items: DrillItem[]; options: CardOption[] }) {
  const drills = useStore(getDrills, {});
  const done = items.filter((i) => drills[i.id]?.revealed);
  const right = done.filter((i) => drills[i.id]?.chosenCard === i.answer).length;
  return (
    <div className="drill">
      <p>
        For each problem, choose the tool and write the property that decides it, without opening the statement's comments
        or tags. Then reveal. Score: {right} right out of {done.length} revealed ({items.length} items).
      </p>
      <ol>{items.map((i) => <Item key={i.id} item={i} state={drills[i.id]} options={options} />)}</ol>
    </div>
  );
}
