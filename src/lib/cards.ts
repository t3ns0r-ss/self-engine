// Card lookup across topics. A topic without a written lesson (or a draft that has no cards
// yet) has no cards; its bank patterns stand in for them (same ids, same preconditions).
import type { SiteData } from './data';

export type CardRef = { topic: string; id: string; name: string; property: string };

export function cardsOfTopic(data: SiteData, topic: string): CardRef[] {
  const tf = data.topics[topic];
  if (tf?.cards.length) return tf.cards.map((c) => ({ topic, id: c.id, name: c.name, property: c.decisive_property }));
  return (data.patterns[topic]?.patterns ?? []).map((p) => ({ topic, id: p.id, name: p.name, property: p.precondition }));
}

/** Every card from topics up to and including `topic` (by curriculum order). */
export function cardsUpTo(data: SiteData, topic: string): CardRef[] {
  const order = data.curriculum.find((t) => t.id === topic)!.order;
  return data.curriculum.filter((t) => t.order <= order).flatMap((t) => cardsOfTopic(data, t.id));
}

/** Display name of a card id; searches `preferTopic` first, then every topic. */
export function cardName(data: SiteData, id: string, preferTopic?: string): string {
  const first = preferTopic ? cardsOfTopic(data, preferTopic).find((c) => c.id === id) : undefined;
  if (first) return first.name;
  for (const t of data.curriculum) {
    const c = cardsOfTopic(data, t.id).find((x) => x.id === id);
    if (c) return `${c.name} (${t.id})`;
  }
  return id;
}
