// Static JSON: the practice exercises (ladder rungs and worked examples) of one design topic, for the lesson's
// "Exercise ladder" list. Practice items are public by design (Section 10.8); reserved items are never listed here.
import type { APIRoute } from 'astro';
import { allExercises, isPractice } from '../../../lib/exercises';
import { url } from '../../../lib/url';

export function getStaticPaths() {
  const topics = [...new Set(allExercises().map((e) => e.topic))];
  return topics.map((topic) => ({ params: { topic } }));
}

export const GET: APIRoute = ({ params }) => {
  const items = allExercises()
    .filter((e) => e.topic === params.topic && isPractice(e))
    .map((e) => ({ globalId: e.globalId, id: e.id, rung: e.rung ?? null, title: e.title, newForce: e.new_force ?? null, type: e.type, role: e.role, href: url(`/${e.track}/exercise/${e.topic}/${e.id}/`) }));
  return new Response(JSON.stringify(items), { headers: { 'Content-Type': 'application/json' } });
};
