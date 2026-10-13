// Per-platform rate gate (PROFILE_SYNC_PLAN.md Section 6): one request in flight at a time, with a minimum gap
// between the end of one request and the start of the next. Clock and sleep are injectable for tests.

export const GAP_MS = { cf: 2100, ac: 1100, lc: 1100 } as const;
export const BACKOFF_MS = [4000, 8000, 16000];

export interface GateDeps {
  now?: () => number;
  sleep?: (ms: number) => Promise<void>;
}
const realSleep = (ms: number) => new Promise<void>((r) => setTimeout(r, ms));

export class Gate {
  private tail: Promise<unknown> = Promise.resolve();
  private lastStart = -Infinity;
  private now: () => number;
  private sleep: (ms: number) => Promise<void>;
  readonly gapMs: number;
  constructor(gapMs: number, deps: GateDeps = {}) {
    this.gapMs = gapMs;
    this.now = deps.now ?? Date.now;
    this.sleep = deps.sleep ?? realSleep;
  }
  /** Runs `fn` after every earlier call has finished and the gap has passed. */
  run<T>(fn: () => Promise<T>): Promise<T> {
    const job = this.tail.then(async () => {
      const wait = this.lastStart + this.gapMs - this.now();
      if (wait > 0) await this.sleep(wait);
      this.lastStart = this.now();
      return fn();
    });
    this.tail = job.catch(() => undefined);
    return job;
  }
}

/** A response with a status that should be retried (429, 503) carries `retryable`. */
export class HttpError extends Error {
  readonly status: number;
  constructor(status: number, message = `HTTP ${status}`) {
    super(message);
    this.status = status;
  }
  get retryable() {
    return this.status === 429 || this.status === 503;
  }
}

/**
 * Calls `fn`; on a retryable error waits 4 s, 8 s, 16 s and tries again, then rethrows the last error
 * (Section 6). Errors that are not retryable are thrown at once.
 */
export async function withBackoff<T>(fn: () => Promise<T>, isRetryable: (e: unknown) => boolean, sleep = realSleep, delays = BACKOFF_MS): Promise<T> {
  for (let attempt = 0; ; attempt++) {
    try {
      return await fn();
    } catch (e) {
      if (attempt >= delays.length || !isRetryable(e)) throw e;
      await sleep(delays[attempt]);
    }
  }
}
