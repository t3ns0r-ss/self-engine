// Codeforces and AtCoder Problems sync (PROFILE_SYNC_PLAN.md Sections 6.1 and 6.2): validated fetches through the
// rate gate, back-off and transport chain, folded into the caches by core.ts. The network pieces are injectable.
import { syncAtCoder, syncCodeforces, type AcSubmission, type Cache, type CfSubmission } from './core.ts';
import { BACKOFF_MS, GAP_MS, Gate, HttpError, withBackoff, type GateDeps } from './gate.ts';
import { acSubmissions, cfUserInfo, cfUserStatus, KNOWN_CF_VERDICTS } from './schemas.ts';
import { getJson, TransportError, type SyncPlatform, type TransportDeps, type TransportName } from './transport.ts';

export interface Net {
  gate: Gate;
  transport: TransportDeps;
  sleep?: (ms: number) => Promise<void>;
}
export interface Counters {
  requests: number;
  transport: TransportName | null;
  unknownVerdicts: Set<string>;
}
export const newCounters = (): Counters => ({ requests: 0, transport: null, unknownVerdicts: new Set() });
export const makeGate = (platform: SyncPlatform, deps?: GateDeps) => new Gate(GAP_MS[platform], deps);

const retryable = (e: unknown) => (e instanceof HttpError && e.retryable) || e instanceof TransportError;

async function call(net: Net, c: Counters, platform: SyncPlatform, method: string, params: Record<string, string | number>): Promise<unknown> {
  return withBackoff(
    () =>
      net.gate.run(async () => {
        c.requests++;
        const r = await getJson({ platform, method, params }, net.transport);
        c.transport = r.transport;
        net.transport.preferred = r.transport;
        return r.data;
      }),
    retryable,
    net.sleep,
    BACKOFF_MS,
  );
}

/** Returns the canonical handle, or throws with the API's comment. */
export async function verifyCfHandle(net: Net, c: Counters, handle: string): Promise<string> {
  const parsed = cfUserInfo.safeParse(await call(net, c, 'cf', 'user.info', { handles: handle }));
  if (!parsed.success) throw new Error('Unexpected response from Codeforces');
  if (parsed.data.status === 'FAILED') throw new Error(parsed.data.comment ?? 'Handle not found or Codeforces unreachable');
  return parsed.data.result[0].handle;
}

export async function syncCf(net: Net, c: Counters, cache: Cache, handle: string): Promise<Cache> {
  return syncCodeforces(cache, async (from, count) => {
    const parsed = cfUserStatus.safeParse(await call(net, c, 'cf', 'user.status', { handle, from, count }));
    if (!parsed.success) throw new Error('Unexpected response from Codeforces (format changed?)');
    if (parsed.data.status === 'FAILED') throw new Error(parsed.data.comment ?? 'Codeforces refused the request');
    for (const s of parsed.data.result) if (s.verdict && !KNOWN_CF_VERDICTS.has(s.verdict)) c.unknownVerdicts.add(s.verdict);
    return parsed.data.result as CfSubmission[];
  });
}

export async function syncAc(net: Net, c: Counters, cache: Partial<Cache>, userId: string): Promise<Cache> {
  return syncAtCoder(cache, async (fromSecond) => {
    const parsed = acSubmissions.safeParse(await call(net, c, 'ac', '', { user: userId, from_second: fromSecond }));
    if (!parsed.success) throw new Error('Unexpected response from AtCoder Problems (format changed?)');
    return parsed.data as AcSubmission[];
  });
}

export const totalTries = (cache: Partial<Cache> | undefined) => Object.values(cache?.problems ?? {}).reduce((n, e) => n + e.tries, 0);
