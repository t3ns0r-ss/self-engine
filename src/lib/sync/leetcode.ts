// LeetCode import (PROFILE_SYNC_PLAN.md Sections 7.4 and 8): validation of the snippet's JSON, the `#lc=` link, and
// the manual submissions-file import. The console snippet itself waits for the S0 probe (Section 8.2).
import { acSubmissions, cfUserStatus, lcPayload, type LcPayload } from './schemas.ts';
import type { AcSubmission, CfSubmission } from './core.ts';

export const MAX_IMPORT_BYTES = 5 * 1024 * 1024;

export type ImportResult =
  | { kind: 'lc'; payload: LcPayload }
  | { kind: 'cf'; submissions: CfSubmission[] }
  | { kind: 'ac'; submissions: AcSubmission[] }
  | { kind: 'error'; message: string };

/** Parses an imported file's text. Never evaluates anything from it. */
export function parseImportText(text: string, bytes = text.length): ImportResult {
  if (bytes > MAX_IMPORT_BYTES) return { kind: 'error', message: 'This file is larger than 5 MB, so it was not read.' };
  let data: unknown;
  try {
    data = JSON.parse(text);
  } catch {
    return { kind: 'error', message: 'This file is not valid JSON.' };
  }
  if (data && typeof data === 'object' && !Array.isArray(data) && 'v' in data) {
    if ((data as { v: unknown }).v !== 1) return { kind: 'error', message: 'This snippet output has an unsupported version. Copy the latest snippet from the Profiles page.' };
    const r = lcPayload.safeParse(data);
    return r.success ? { kind: 'lc', payload: r.data } : { kind: 'error', message: 'The LeetCode result has the wrong shape.' };
  }
  const cf = cfUserStatus.safeParse(data);
  if (cf.success && cf.data.status === 'OK') return { kind: 'cf', submissions: cf.data.result as CfSubmission[] };
  const ac = acSubmissions.safeParse(data);
  if (ac.success && Array.isArray(data) && data.length > 0) return { kind: 'ac', submissions: ac.data as AcSubmission[] };
  return { kind: 'error', message: 'This file is not a LeetCode snippet result, a Codeforces user.status response, or an AtCoder Problems submissions list.' };
}

/** `#lc=<base64url JSON>` -> JSON text, or null when the hash carries no payload. */
export function decodeLcFragment(hash: string): string | null {
  const m = /^#?lc=([A-Za-z0-9_-]+)$/.exec(hash);
  if (!m) return null;
  try {
    const b64 = m[1].replace(/-/g, '+').replace(/_/g, '/');
    const bin = atob(b64 + '='.repeat((4 - (b64.length % 4)) % 4));
    return new TextDecoder().decode(Uint8Array.from(bin, (ch) => ch.charCodeAt(0)));
  } catch {
    return null;
  }
}
