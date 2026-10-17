// Numeric answer box (Section 11.3): a number and a unit, checked with the exercise's factor; then both numbers and the derivation.
import { useState } from 'react';
import { numericOk } from '../../lib/design-client';

export default function NumericAnswer({ reference, unit, factor = 2, derivation }: { reference: number; unit: string; factor?: number; derivation?: string }) {
  const [value, setValue] = useState('');
  const [free, setFree] = useState(unit);
  const [shown, setShown] = useState(false);
  const n = Number(value);
  return (
    <div className="numeric-answer">
      <label>Your answer <input inputMode="decimal" value={value} onChange={(e) => setValue(e.target.value)} /></label>{' '}
      <label>Unit <input value={free} onChange={(e) => setFree(e.target.value)} /></label>{' '}
      <button type="button" disabled={!(n > 0)} onClick={() => setShown(true)}>Check</button>
      {shown && (
        <div>
          <p><strong>{numericOk(n, reference, factor) ? 'Within the factor.' : 'Outside the factor.'}</strong> You: {n} {free}. Reference: {reference} {unit}. Accepted: between {reference / factor} and {reference * factor}.</p>
          {derivation && <pre className="derivation">{derivation}</pre>}
        </div>
      )}
    </div>
  );
}
