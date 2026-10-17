// Static JSON: every card of a design track in curriculum order, for the Drill component's answer list.
// Card names are not reserved material, so this file may be public.
import type { APIRoute } from 'astro';
import { loadData } from '../../../lib/data';

export function getStaticPaths() {
  return [{ params: { track: 'lld' } }, { params: { track: 'hld' } }];
}

export const GET: APIRoute = async ({ params }) => {
  const data = await loadData();
  const out = data.designCurriculum
    .filter((t) => t.track === params.track)
    .flatMap((t) => (data.designTopics[t.id]?.cards ?? []).map((c) => ({ topic: t.id, card: c.id, name: c.name, order: t.order })));
  return new Response(JSON.stringify(out), { headers: { 'Content-Type': 'application/json' } });
};
