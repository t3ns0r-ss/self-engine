// Static JSON endpoint: /data/reserved/{topic}.json holds only that topic's reserved exercises.
// Drill, Checkpoint, Review, and Exam components fetch it in the browser on demand.
import type { APIRoute } from 'astro';
import { allExercises, isPractice } from '../../../lib/exercises';

export function getStaticPaths() {
  const topics = [...new Set(allExercises().map((e) => e.topic))];
  return topics.map((topic) => ({ params: { topic } }));
}

export const GET: APIRoute = ({ params }) => {
  const reserved = allExercises().filter((e) => e.topic === params.topic && !isPractice(e));
  return new Response(JSON.stringify(reserved), { headers: { 'Content-Type': 'application/json' } });
};
