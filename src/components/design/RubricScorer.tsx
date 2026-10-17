// Rubric scoring (Section 11.2): anchors per criterion, a 0/1/2 selector, an evidence note, score and pass/fail.
import { useState } from 'react';
import { addDesignAttempt, today } from '../../lib/storage';
import { rubricPasses, rubricPercent } from '../../lib/design-client';

export type RubricCriterion = { id: string; name: string; weight: number; critical: boolean; critical_when?: string; anchors: Record<'0' | '1' | '2', string> };
export type Rubric = { id: string; name: string; criteria: RubricCriterion[] };

export default function RubricScorer({ rubric, globalId, minutes = null, onResult }: { rubric: Rubric; globalId: string; minutes?: number | null; onResult?: (pass: boolean, percent: number) => void }) {
  const [scores, setScores] = useState<Record<string, { score: 0 | 1 | 2; evidence: string }>>({});
  const [whenOn, setWhenOn] = useState<Record<string, boolean>>({});
  const [saved, setSaved] = useState(false);
  const pct = rubricPercent(rubric.criteria, scores);
  const pass = rubricPasses(rubric.criteria, scores, whenOn);
  const set = (id: string, patch: Partial<{ score: 0 | 1 | 2; evidence: string }>) => setScores((s) => ({ ...s, [id]: { score: 0, evidence: '', ...s[id], ...patch } }));
  return (
    <div className="rubric-scorer">
      <h4>{rubric.name}</h4>
      {rubric.criteria.map((c) => (
        <fieldset key={c.id}>
          <legend>{c.name} (weight {c.weight}{c.critical ? ', critical' : ''})</legend>
          {c.critical_when && (
            <label><input type="checkbox" checked={!!whenOn[c.id]} onChange={(e) => setWhenOn((w) => ({ ...w, [c.id]: e.target.checked }))} /> Critical here: {c.critical_when}</label>
          )}
          {(['0', '1', '2'] as const).map((k) => (
            <label key={k} className="anchor">
              <input type="radio" name={`${globalId}-${c.id}`} checked={(scores[c.id]?.score ?? -1) === Number(k)} onChange={() => set(c.id, { score: Number(k) as 0 | 1 | 2 })} /> <strong>{k}</strong> {c.anchors[k]}
            </label>
          ))}
          <label>Evidence note <input value={scores[c.id]?.evidence ?? ''} onChange={(e) => set(c.id, { evidence: e.target.value })} /></label>
        </fieldset>
      ))}
      <p><strong>Score: {pct.toFixed(0)}%</strong>. {pass ? 'Passes' : 'Does not pass yet'} (needs 70%, every critical criterion at least 1 with an evidence note).</p>
      <button type="button" disabled={saved} onClick={() => { setSaved(addDesignAttempt(globalId, { date: today(), minutes, scores, testsPassed: pass })); onResult?.(pass, pct); }}>{saved ? 'Saved' : 'Save this attempt'}</button>
    </div>
  );
}
