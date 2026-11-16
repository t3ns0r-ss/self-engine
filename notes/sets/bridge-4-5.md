# Bridge set, Phase 4 to 5: solution notes (private, not rendered)

Every statement was opened and read on 2026-11-16 (AtCoder, `source_check: page`). Each entry: the budget, the whole idea (so the `new_idea` line can be
checked), and the Phase 4 tools it rests on. None needs a Phase 5 topic.

## ac-abc239_f Construct Highway (1959)
- Budget: N <= 2e5, near-linear. Idea: components of the given M edges (union-find); each component has unused degree r_c = sum D_i - 2 * edges inside; need N - M - 1 new edges, so the sum of r_c must be 2 (components - 1) and every r_c >= 1. Build a tree from this degree list: pair a component with r = 1 to a component with r >= 2, repeat; the last two components have r = 1. Pick a concrete town with free degree inside each component. Tools: 4.1 components, 4.5 union-find. New: tree from a degree sequence (leaves hang on nodes with spare degree).

## ac-abc229_f Make Bipartite (1917)
- Budget: N <= 2e5. Idea: remove edges to get a 2-colouring; vertex 0 is joined to every cycle vertex. Fix colour of 0 (2 choices); then DP around the cycle 1..N with state = colour of vertex i and colour of vertex 1 (to close the cycle); cost = weight of the edges whose ends are equal. 2 x 2 x 2 states, O(N). Tools: 4.2 bipartite means 2-colouring. New: fix one vertex, DP around a cycle.

## ac-abc142_f Pure (1919)
- Budget: N <= 1000, M <= 2000. Idea: every vertex of the induced subgraph has in- and out-degree 1, so it is a single directed cycle with no extra edge between its vertices. A shortest cycle has no such extra edge (it would shorten the cycle), so take the shortest cycle over BFS from every vertex: O(N (N + M)). No cycle: -1. Tools: 4.1 BFS, 4.2 cycle. New: a shortest cycle is automatically chordless.

## ac-abc260_f Find 4-cycle (1995)
- Budget: S <= 3e5, T <= 3000, M <= 3e5. Idea: a 4-cycle is two left vertices sharing two right neighbours. For each left vertex list its right neighbours and look at every pair (a, b); if the pair was seen before, output the two left vertices and the pair; otherwise store it. At most T(T-1)/2 + 1 pair visits happen before a repeat (pigeonhole), about 4.5e6. Tools: 4.1 adjacency lists, 4.2 bipartite. New: pigeonhole bound on pairs.

## ac-abc181_f Silver Woods (2009)
- Budget: N <= 100. Idea: circle of radius r passes iff top and bottom are not joined by a chain of obstacles with consecutive gaps < 2r. Nodes: nails, top wall (y = 100), bottom wall (y = -100). Weight of nail-nail = distance, nail-wall = distance to the line, wall-wall = 200. Kruskal order; stop when top and bottom are joined; answer = (that weight) / 2. Tools: 4.5 Kruskal and union-find. New: bottleneck connection of two special nodes; walls as nodes.

## ac-abc375_g Road Blocked 2 (2014)
- Budget: N, M <= 2e5. Idea: Dijkstra from 1 and from N; edge (u, v, c) is on a shortest path iff d1[u] + c + dN[v] = D (either direction). Among these edges the removal changes the distance exactly when the edge is a bridge of that undirected subgraph; other edges never change it. Tools: 4.3 Dijkstra, 4.8 bridges. New: shortest-path subgraph plus bridges.

## ac-abc369_g As far as possible (2055)
- Budget: N <= 2e5. Idea: for K vertices the best (for Aoki) choice gives walk length 2 x (total weight of the union of the root paths); union weight is maximised greedily by long-path decomposition: root at 1, chain through the child with the deepest leaf; sort chain weights descending; answer for K is twice the sum of the K largest chains. Tools: 4.6 DFS and depth. New: long-path decomposition.

## ac-abc359_g Sum of Tree Distance (2099)
- Budget: N <= 2e5. Idea: dist(i, j) = dep_i + dep_j - 2 dep_lca. For every vertex keep a map colour -> (count, sum of depths) of its subtree; merge the smaller map into the larger; when merging a (count a, sum A) into (count b, sum B) of the same colour at vertex v add a*B + b*A - 2 dep_v * a * b. O(N log N) map updates overall. Tools: 4.6 subtree DFS, 4.7 depth and lca formula. New: small-to-large merging of per-colour tables.

## ac-abc295_g Minimum Reachable City (2091)
- Budget: N, Q <= 2e5. Idea: the graph G_S is a tree (parent index < child index) and an added edge u -> v has v an ancestor of u, so together with the tree path v .. u it closes a cycle: all those vertices become one strongly connected component. Maintain a union-find over components storing the minimum label; for the edge walk up from u merging with parent until reaching v's component. A vertex is merged with its parent at most once. Query: minimum label of x's component (smaller labels are ancestors, and everything above x that is reachable is in x's component). Tools: 4.8 SCC idea, 4.5 union-find. New: contract the cycle path into one component.

## ac-abc197_f Construct a Palindrome (1945)
- Budget: N, M <= 1000. Idea: a palindromic string is built from both ends: state (u, v) = current ends, start (1, N); move both ends along edges that carry the same letter; BFS over pairs. The shortest palindrome has length 2 d if some state (a, a) is reached after d steps, or 2 d + 1 if some state (a, b) with an edge a - b is reached after d steps (the middle letter). N^2 = 1e6 states, transitions bounded by (sum of degrees)^2 = 4e6. Tools: 4.1 BFS, 4.4 state graph. New: grow from both ends.

## ac-abc258_g Triangle (1944)
- Budget: N <= 3000, N^3 = 2.7e10 is too slow, N^3 / 64 = 4.2e8 fits. Idea: for every edge (i, j) with i < j count common neighbours k > j as popcount(row_i AND row_j) restricted to bits above j (or count all and divide by 3). Tools: 4.1 adjacency matrix, 1.7 bit operations. New: bitset AND-popcount to count triangles.

## ac-abc233_f Swap and Sort (2038)
- Budget: N <= 1000, M <= 2e5, at most 5e5 swaps (N(N-1)/2 = 499500). Idea: the values of each connected component of the swap graph must be exactly the positions of the component, otherwise no. Take a spanning tree of each component. Repeatedly pick a leaf, bring the value that belongs there to it by swapping along the tree path (at most size - 1 swaps), delete the leaf. Total at most N(N-1)/2 swaps. Tools: 4.5 union-find, 4.6 tree paths. New: sort by peeling leaves of a spanning tree.
