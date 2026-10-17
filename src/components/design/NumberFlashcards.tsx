// Number flashcards (Section 11.4): guess a constant on a log-scale slider; correct within one order of magnitude;
// spaced at 1, 3, 7 and 21 days. The learner's own measured values are entered once on the Numbers page.
import { useState } from 'react';
import { NUMBER_INTERVALS, addDays, getNumbers, saveNumber, today } from '../../lib/storage';
import { useStore } from '../../lib/useStore';
import { withinOneOrder } from '../../lib/design-client';

export type Constant = { id: string; quantity: string; value: number; unit: string; display: string; caveat: string };

export default function NumberFlashcards({ constants }: { constants: Constant[] }) {
  const cards = useStore(getNumbers, {});
  const due = constants.filter((c) => !cards[c.id]?.due || cards[c.id].due! <= today());
  const [i, setI] = useState(0);
  const [exp, setExp] = useState(0);        // slider value: the exponent of 10
  const [shown, setShown] = useState(false);
  if (!constants.length) return <p className="muted">No constants yet.</p>;
  if (!due.length) return <p>Nothing due today.</p>;
  const c = due[i % due.length];
  const guess = 10 ** exp;
  const ok = withinOneOrder(guess, c.value);
  const next = () => {
    const box = Math.min((cards[c.id]?.box ?? 0) + (ok ? 1 : -1), NUMBER_INTERVALS.length - 1);
    const b = Math.max(box, 0);
    saveNumber(c.id, { box: b, due: addDays(today(), NUMBER_INTERVALS[ok ? b : 0]) });
    setShown(false); setExp(0); setI(i + 1);
  };
  return (
    <div className="number-flashcard">
      <p><strong>{c.quantity}</strong> ({c.unit})</p>
      <label>Guess (log scale) <input type="range" min={-9} max={18} step={0.25} value={exp} disabled={shown} onChange={(e) => setExp(Number(e.target.value))} /></label>
      <p>Your guess: 10^{exp} = {guess.toExponential(2)} {c.unit}</p>
      {!shown ? <button type="button" onClick={() => setShown(true)}>Reveal</button> : (
        <>
          <p><strong>{ok ? 'Within one order of magnitude.' : 'More than one order of magnitude away.'}</strong> Value: {c.display} ({c.value} {c.unit}). {c.caveat}</p>
          <button type="button" onClick={next}>Next</button>
        </>
      )}
    </div>
  );
}
