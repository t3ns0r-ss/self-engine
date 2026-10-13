// Response and import validation for the three platforms (PROFILE_SYNC_PLAN.md Sections 6, 7.4, 8).
import { z } from 'zod';

export const cfSubmission = z.object({
  id: z.number(),
  creationTimeSeconds: z.number(),
  problem: z.object({ contestId: z.number().optional(), index: z.string() }),
  verdict: z.string().optional(),
});
export const cfUserStatus = z.discriminatedUnion('status', [
  z.object({ status: z.literal('OK'), result: z.array(cfSubmission) }),
  z.object({ status: z.literal('FAILED'), comment: z.string().optional() }),
]);
export const cfUserInfo = z.discriminatedUnion('status', [
  z.object({ status: z.literal('OK'), result: z.array(z.object({ handle: z.string() })).min(1) }),
  z.object({ status: z.literal('FAILED'), comment: z.string().optional() }),
]);

export const acSubmission = z.object({
  id: z.number(),
  epoch_second: z.number(),
  problem_id: z.string(),
  result: z.string(),
});
export const acSubmissions = z.array(acSubmission);

/** Output of the LeetCode console snippet (Section 8.3). */
export const lcPayload = z.object({
  v: z.literal(1),
  username: z.string().min(1).max(100),
  at: z.number().int().positive(),
  method: z.enum(['list', 'perproblem']),
  statuses: z.record(z.string().max(200), z.enum(['ac', 'notac'])),
});
export type LcPayload = z.infer<typeof lcPayload>;

/** Verdicts the Codeforces API documents; anything else is counted as an attempt and logged (Section 18). */
export const KNOWN_CF_VERDICTS = new Set([
  'FAILED', 'OK', 'PARTIAL', 'COMPILATION_ERROR', 'RUNTIME_ERROR', 'WRONG_ANSWER', 'PRESENTATION_ERROR',
  'TIME_LIMIT_EXCEEDED', 'MEMORY_LIMIT_EXCEEDED', 'IDLENESS_LIMIT_EXCEEDED', 'SECURITY_VIOLATED', 'CRASHED',
  'INPUT_PREPARATION_CRASHED', 'CHALLENGED', 'SKIPPED', 'TESTING', 'REJECTED',
]);
