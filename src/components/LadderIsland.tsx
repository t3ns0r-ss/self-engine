import { useState } from 'react';
import { STATUS_LABELS, isSolved, saveProblem, type ProblemLog } from '../lib/storage';
import { useProblems } from '../lib/useProblems';
import LogPanel from './LogPanel';
import PlatformBadge from './PlatformBadge';

export type LadderProblem = {
  id: string; title: string; url: string; source: string; difficulty: string;
  rung: number; twist: string; summary: string; hints: string[]; editorial_url: string | null;
};
export type LadderGroup = { card: { id: string; name: string }; problems: LadderProblem[] };
export type ExtraProblem = { id: string; title: string; url: string; source: string; difficulty: string; tier: number; pattern: string };

function Hints({ p, log, budget }: { p: LadderProblem; log?: ProblemLog; budget: string }) {
  const opened = log?.hintsOpened ?? 0;
  const [asking, setAsking] = useState(false);
  const next = opened + 1;
  return (
    <div className="hints">
      {p.hints.slice(0, opened).map((h, i) => (
        <p key={i} className="hint"><strong>Hint {i + 1}:</strong> {h}</p>
      ))}
      {next <= p.hints.length &&
        (asking ? (
          <div className="hint-reminder" role="alert">
            <p>
              {next === 1
                ? `Struggle budget: work on the problem for at least ${budget} before Hint 1. Have you written the budget, candidate tools, and property?`
                : 'Wait at least 10 minutes after the previous hint and try again before opening the next one.'}
            </p>
            <button type="button" onClick={() => { saveProblem(p.id, { hintsOpened: next }); setAsking(false); }}>Show hint {next}</button>{' '}
            <button type="button" className="secondary" onClick={() => setAsking(false)}>Keep trying</button>
          </div>
        ) : (
          <button type="button" className="secondary" onClick={() => setAsking(true)}>Hint {next}</button>
        ))}
      {p.editorial_url && opened >= p.hints.length && (
        <p><a href={p.editorial_url} target="_blank" rel="noopener noreferrer">Editorial</a> (log "Read editorial" if you use it)</p>
      )}
    </div>
  );
}

export default function LadderIsland({ groups, more, budget }: { groups: LadderGroup[]; more: ExtraProblem[]; budget: string }) {
  const logs = useProblems();
  const [open, setOpen] = useState<string | null>(null);
  return (
    <div className="ladder">
      {groups.map((g) => {
        const solved = g.problems.filter((p) => isSolved(logs[p.id])).length;
        return (
          <section key={g.card.id} className="ladder-group">
            <h3 id={`ladder-${g.card.id}`}>{g.card.name}</h3>
            <div className="progress" aria-label={`${solved} of ${g.problems.length} solved`}>
              <div style={{ width: `${(100 * solved) / Math.max(1, g.problems.length)}%` }} />
              <span>{solved} / {g.problems.length} solved</span>
            </div>
            {g.problems.map((p) => {
              const log = logs[p.id];
              return (
                <article key={p.id} className={`ladder-item${log?.status ? ` status-${log.status}` : ''}`}>
                  <header>
                    <span className="rung">Rung {p.rung}</span>{' '}
                    <a href={p.url} target="_blank" rel="noopener noreferrer">{p.title}</a>{' '}
                    <PlatformBadge source={p.source} /> <span className="muted">{p.difficulty}</span>
                  </header>
                  <p><strong>New twist:</strong> {p.twist}</p>
                  <p>{p.summary}</p>
                  <Hints p={p} log={log} budget={budget} />
                  <div className="ladder-status">
                    <span>{log?.status ? STATUS_LABELS[log.status] : 'Not started'}</span>
                    {log?.hintsOpened ? <span className="muted"> · {log.hintsOpened} hint{log.hintsOpened > 1 ? 's' : ''} opened</span> : null}{' '}
                    <button type="button" className="secondary" aria-expanded={open === p.id} onClick={() => setOpen(open === p.id ? null : p.id)}>Log</button>
                  </div>
                  {open === p.id && <LogPanel id={p.id} log={log} onDone={() => setOpen(null)} />}
                </article>
              );
            })}
          </section>
        );
      })}
      {more.length > 0 && (
        <section>
          <h3 id="more-practice">More practice</h3>
          <p>Extra problems from the bank for this topic, easiest tier first. No hints.</p>
          <ul className="more-practice">
            {more.map((p) => (
              <li key={p.id} className={logs[p.id]?.status ? `status-${logs[p.id]!.status}` : undefined}>
                <a href={p.url} target="_blank" rel="noopener noreferrer">{p.title}</a> <PlatformBadge source={p.source} /> {p.difficulty} · tier {p.tier} · {p.pattern}
                {logs[p.id]?.status ? ` · ${STATUS_LABELS[logs[p.id]!.status!]}` : ''}
              </li>
            ))}
          </ul>
        </section>
      )}
    </div>
  );
}
