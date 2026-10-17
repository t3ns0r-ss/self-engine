// Countdown with phase shares (Section 11.2). The start time is kept in memory; reloading restarts the clock.
import { useEffect, useState } from 'react';
import { TIMER_PHASES, phaseAt } from '../../lib/design-client';

export default function PhaseTimer({ minutes, kind, autoStart = false }: { minutes: number; kind: keyof typeof TIMER_PHASES | null; autoStart?: boolean }) {
  const [startedAt, setStartedAt] = useState<number | null>(autoStart ? Date.now() : null);
  const [now, setNow] = useState(Date.now());
  useEffect(() => { if (startedAt === null) return; const id = setInterval(() => setNow(Date.now()), 1000); return () => clearInterval(id); }, [startedAt]);
  if (startedAt === null) return <button type="button" onClick={() => { setStartedAt(Date.now()); setNow(Date.now()); }}>Start the {minutes}-minute timer</button>;
  const elapsed = (now - startedAt) / 60000;
  const left = Math.max(0, minutes * 60 - Math.floor((now - startedAt) / 1000));
  const phase = kind ? phaseAt(kind, elapsed, minutes) : -1;
  return (
    <div className="phase-timer" role="timer" aria-live="off">
      <p><strong>{String(Math.floor(left / 60)).padStart(2, '0')}:{String(left % 60).padStart(2, '0')}</strong> left{left === 0 ? ': time is up' : ''}.</p>
      {kind && (
        <ol>
          {TIMER_PHASES[kind].map(([label, pct], i) => (
            <li key={label} style={{ fontWeight: i === phase ? 700 : 400 }}>{label}: {Math.round((pct / 100) * minutes)} min{i === phase ? ' (now)' : ''}</li>
          ))}
        </ol>
      )}
    </div>
  );
}
