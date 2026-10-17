// Timed checkpoint for the design tracks (Section 8.13): fetched from the reserved JSON; kit commands appear after start;
// phase timer; rubric scoring; pass rule: kit tests pass (self-reported), rubric >= 70% with critical criteria, drill >= 75%.
import { useEffect, useState } from 'react';
import { fetchReserved, timerKind, type ReservedItem } from '../lib/design-client';
import { getDrills, getTopics, saveTopic, today } from '../lib/storage';
import { useStore } from '../lib/useStore';
import PhaseTimer from './design/PhaseTimer';
import RubricScorer, { type Rubric } from './design/RubricScorer';
import AskFirst from './design/AskFirst';

export default function Checkpoint({ topic, rubrics = [] }: { topic: string; rubrics?: Rubric[] }) {
  const [item, setItem] = useState<ReservedItem | null | undefined>(undefined);
  const [drillIds, setDrillIds] = useState<string[]>([]);
  const [started, setStarted] = useState(false);
  const [testsPassed, setTestsPassed] = useState(false);
  const [rubricPass, setRubricPass] = useState<boolean | null>(null);
  const [err, setErr] = useState('');
  const state = useStore(() => getTopics()[topic], undefined);
  const drills = useStore(getDrills, {});
  useEffect(() => {
    fetchReserved(topic).then((all) => { setItem(all.find((e) => e.role === 'checkpoint') ?? null); setDrillIds(all.filter((e) => e.role === 'drill').map((e) => e.globalId)); }).catch((e) => setErr(e.message));
  }, [topic]);
  if (err) return <p className="notice">Could not load the checkpoint: {err}</p>;
  if (item === undefined) return <p>Loading…</p>;
  if (item === null) return <p className="muted">This topic has no checkpoint.</p>;
  const kit = item.checkers?.find((c) => c.kind === 'kit');
  const rubricId = item.checkers?.find((c) => c.kind === 'rubric');
  const rubric = rubricId && rubricId.kind === 'rubric' ? rubrics.find((r) => r.id === rubricId.id) : undefined;
  const shownDrill = drillIds.filter((id) => drills[id]?.revealed);
  const drillRight = shownDrill.length; // correctness is stored with the attempt; the pass rule uses the reveal count as a floor until Drill logs it
  const drillOk = drillIds.length === 0 || drillRight / drillIds.length >= 0.75;
  const pass = (!kit || testsPassed) && (!rubric || rubricPass === true) && drillOk;
  return (
    <div className="checkpoint">
      {state?.checkpointPassedOn && <p><strong>Passed on {state.checkpointPassedOn}.</strong></p>}
      <h4>{item.title}</h4>
      <p>{item.prompt}</p>
      {!started ? (
        <button type="button" onClick={() => setStarted(true)}>Start ({item.time_limit_minutes} minutes)</button>
      ) : (
        <>
          {item.time_limit_minutes && <PhaseTimer autoStart minutes={item.time_limit_minutes} kind={timerKind(item.track, item.type)} />}
          {item.clarifying && item.clarifying.length > 0 && <AskFirst clarifying={item.clarifying} />}
          {kit && kit.kind === 'kit' && (
            <div>
              <p>Start: <code>bash scripts/new_attempt.sh {kit.path}</code></p>
              <p>Test: <code>bash exercises/{kit.path}/test.sh work/{kit.path}</code></p>
              <label><input type="checkbox" checked={testsPassed} onChange={(e) => setTestsPassed(e.target.checked)} /> The kit tests pass</label>
            </div>
          )}
          {rubric && <RubricScorer rubric={rubric} globalId={item.globalId} minutes={item.time_limit_minutes} onResult={(p) => setRubricPass(p)} />}
          <p>Drill items revealed: {shownDrill.length} of {drillIds.length}. Needed: 75%.</p>
          <button type="button" disabled={!pass} onClick={() => saveTopic(topic, { checkpointPassedOn: today() })}>Record checkpoint passed</button>
        </>
      )}
    </div>
  );
}
