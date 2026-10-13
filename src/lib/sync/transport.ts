// Transport chain (PROFILE_SYNC_PLAN.md Section 7): direct fetch, then JSONP (Codeforces only), then the optional
// same-origin proxy. The transport that last worked for a platform is tried first. Network pieces are injectable.
import { HttpError } from './gate.ts';

export type SyncPlatform = 'cf' | 'ac';
export type TransportName = 'direct' | 'jsonp' | 'proxy';
export interface Request {
  platform: SyncPlatform;
  /** Codeforces: the method name, e.g. "user.status". AtCoder Problems: ignored (one endpoint). */
  method: string;
  params: Record<string, string | number>;
}
export interface TransportDeps {
  fetch?: typeof fetch;
  /** Loads a JSONP url and resolves to the callback's argument. Default: a script element (browser only). */
  loadJsonp?: (url: string, timeoutMs: number) => Promise<unknown>;
  /** Base path of the same-origin proxy (from sync-config.json), or null/undefined when there is none. */
  proxyBase?: string | null;
  /** Transport that last worked for this platform. */
  preferred?: TransportName;
}
export class TransportError extends Error {
  readonly causes: string[];
  constructor(message: string, causes: string[]) {
    super(message);
    this.causes = causes;
  }
}

const query = (params: Request['params']) =>
  Object.entries(params).map(([k, v]) => `${encodeURIComponent(k)}=${encodeURIComponent(String(v))}`).join('&');

export function directUrl(r: Request): string {
  return r.platform === 'cf'
    ? `https://codeforces.com/api/${r.method}?${query(r.params)}`
    : `https://kenkoooo.com/atcoder/atcoder-api/v3/user/submissions?${query(r.params)}`;
}
export function proxyUrl(r: Request, proxyBase: string): string {
  const base = proxyBase.replace(/\/$/, '');
  return r.platform === 'cf'
    ? `${base}/cf/api/${r.method}?${query(r.params)}`
    : `${base}/ac/atcoder/atcoder-api/v3/user/submissions?${query(r.params)}`;
}

async function viaFetch(url: string, f: typeof fetch): Promise<unknown> {
  const res = await f(url, { credentials: 'omit', referrerPolicy: 'no-referrer' });
  if (res.status === 429 || res.status === 503) throw new HttpError(res.status);
  let body: unknown;
  try {
    body = await res.json();
  } catch {
    throw new HttpError(res.status || 502, `Unreadable response (HTTP ${res.status})`);
  }
  // A readable error body (for example Codeforces status FAILED on HTTP 400) is a real answer.
  if (!res.ok && (body === null || typeof body !== 'object')) throw new HttpError(res.status);
  return body;
}

/** Default JSONP loader: runs Codeforces' response as a script, so it is used only after direct fetch failed. */
export function scriptJsonp(url: string, timeoutMs: number, doc: Document = document, win: Record<string, unknown> = window as never): Promise<unknown> {
  return new Promise((resolve, reject) => {
    const name = `__cpJsonp${Date.now().toString(36)}${Math.floor(Math.random() * 1e9).toString(36)}`;
    const script = doc.createElement('script');
    let done = false;
    const finish = (fn: () => void) => {
      if (done) return;
      done = true;
      clearTimeout(timer);
      script.remove();
      delete win[name];
      fn();
    };
    win[name] = (data: unknown) => finish(() => resolve(data));
    script.onerror = () => finish(() => reject(new TypeError('JSONP script failed to load')));
    const timer = setTimeout(() => finish(() => reject(new TypeError('JSONP timed out'))), timeoutMs);
    script.src = `${url}&jsonp=${name}`;
    doc.head.appendChild(script);
  });
}

/** Fetches one API response as JSON, trying transports in order. Throws HttpError for 429/503 and TransportError otherwise. */
export async function getJson(r: Request, deps: TransportDeps = {}): Promise<{ data: unknown; transport: TransportName }> {
  const f = deps.fetch ?? globalThis.fetch?.bind(globalThis);
  const jsonp = deps.loadJsonp ?? ((u: string, t: number) => scriptJsonp(u, t));
  const order: TransportName[] = ['direct'];
  if (r.platform === 'cf') order.push('jsonp');
  if (deps.proxyBase) order.push('proxy');
  if (deps.preferred && order.includes(deps.preferred)) order.sort((a, b) => (a === deps.preferred ? -1 : b === deps.preferred ? 1 : 0));
  const causes: string[] = [];
  for (const t of order) {
    try {
      if (t === 'direct') return { data: await viaFetch(directUrl(r), f), transport: t };
      if (t === 'jsonp') return { data: await jsonp(directUrl(r), 15000), transport: t };
      return { data: await viaFetch(proxyUrl(r, deps.proxyBase as string), f), transport: t };
    } catch (e) {
      if (e instanceof HttpError) throw e; // the server answered; another route will not help
      causes.push(`${t}: ${e instanceof Error ? e.message : String(e)}`);
    }
  }
  throw new TransportError('Could not reach the platform from this site address', causes);
}
