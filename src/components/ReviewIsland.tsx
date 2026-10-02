import { useState } from 'react';
import { REVIEW_OFFSETS, STATUS_LABELS, addDays, getTopics } from '../lib/storage';
import { useProblems } from '../lib/useProblems';
import { useStore } from '../lib/useStore';
import LogPanel from './LogPanel';
import PlatformBadge from './PlatformBadge';

export type ReviewProblem = { id: string; title: string; url: string; source: string; difficulty: string; summary: string; card: string; property: string };

export default function ReviewIsland({ topic, set, problems }: { topic: string; set: 1 | 2 | 3; problems: ReviewProblem[] }) {
  const passed = useStore(() => getTopics()[topic]?.checkpointPassedOn ?? null, null);
  const logs = useProblems();
  const [showAnyway, setShowAnyway] = useState(false);
  const [revealed, setRevealed] = useState<Record<string, boolean>>({});
  const [open, setOpen] = useState<string | null>(null);

  if (!passed && !showAnyway) {
    return (
      <div className="notice">
        <p>This review set unlocks when you pass the topic's checkpoint. Seeing the problems early spoils them for review.</p>
        <button type="button" className="secondary" onClick={() => setShowAnyway(true)}>Show anyway</button>
      </div>
    );
  }
  return (
    <div className="review">
      {passed && <p>Due on <strong>{addDays(passed, REVIEW_OFFSETS[set])}</strong>.</p>}
      {problems.map((p) => {
        const log = logs[p.id];
        return (
          <article key={p.id} className={`ladder-item${log?.status ? ` status-${log.status}` : ''}`}>
            <header>
              <a href={p.url} target="_blank" rel="noopener noreferrer">{p.title}</a> <PlatformBadge source={p.source} /> <span className="muted">{p.difficulty}</span>
            </header>
            <p>{p.summary}</p>
            {revealed[p.id] ? (
              <p className="drill-answer"><strong>Tool:</strong> {p.card}. <strong>Property:</strong> {p.property}</p>
            ) : (
              <button type="button" className="secondary" onClick={() => setRevealed({ ...revealed, [p.id]: true })}>Reveal tool and property</button>
            )}{' '}
            <span>{log?.status ? STATUS_LABELS[log.status] : 'Not started'}</span>{' '}
            <button type="button" className="secondary" onClick={() => setOpen(open === p.id ? null : p.id)}>Log</button>
            {open === p.id && <LogPanel id={p.id} log={log} onDone={() => setOpen(null)} />}
          </article>
        );
      })}
    </div>
  );
}
