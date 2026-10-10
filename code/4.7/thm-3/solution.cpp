#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<pair<int, int>>>;

// Theorem 4.7.1. adj[v] holds (neighbour, edge number) pairs, vertices are 1..n, edges 0..m-1 (parallel edges differ); parentEdge is -1 at a root.
struct LowLink {
    vector<int> tin, low, parent, parentEdge, order;
    LowLink(const vector<vector<pair<int, int>>>& adj) {
        int n = adj.size() - 1, timer = 0;
        tin.assign(n + 1, -1), low.assign(n + 1, 0), parent.assign(n + 1, 0), parentEdge.assign(n + 1, -1);
        vector<int> next(n + 1, 0);  // next[v]: how many neighbours of v were looked at
        for (int root = 1; root <= n; root++) {
            if (tin[root] != -1) continue;
            vector<int> stack = {root};
            tin[root] = low[root] = timer++, order.push_back(root);
            while (!stack.empty()) {
                int v = stack.back();
                if (next[v] < (int)adj[v].size()) {
                    auto [to, id] = adj[v][next[v]++];
                    if (id == parentEdge[v]) continue;  // the edge we came by, not a second one to the parent
                    if (tin[to] != -1) low[v] = min(low[v], tin[to]);  // a back edge
                    else {
                        parent[to] = v, parentEdge[to] = id;
                        tin[to] = low[to] = timer++, order.push_back(to);
                        stack.push_back(to);
                    }
                } else {
                    stack.pop_back();
                    if (parent[v]) low[parent[v]] = min(low[parent[v]], low[v]);  // the subtree of v is done
                }
            }
        }
    }
};

// snippet:begin
// Theorem 4.7.3. A vertex that is not a root is an articulation point when some child c has low[c] >= tin[v]; a root needs two children.
vector<int> findArticulationPoints(const Graph& adj) {
    LowLink L(adj);
    int n = adj.size() - 1;
    vector<int> children(n + 1, 0);
    vector<bool> cut(n + 1, false);
    for (int c = 1; c <= n; c++) {
        int p = L.parent[c];
        if (!p) continue;
        children[p]++;
        if (L.parent[p] && L.low[c] >= L.tin[p]) cut[p] = true;
    }
    vector<int> points;
    for (int v = 1; v <= n; v++)
        if (cut[v] || (!L.parent[v] && children[v] >= 2)) points.push_back(v);
    return points;
}
// snippet:end

// Test helpers: build a graph from an edge list, random multigraphs, and the number of components with some edge or vertex left out.
Graph build(int n, const vector<pair<int, int>>& edges) {
    Graph adj(n + 1);
    for (int i = 0; i < (int)edges.size(); i++) {
        adj[edges[i].first].push_back({edges[i].second, i});
        adj[edges[i].second].push_back({edges[i].first, i});
    }
    return adj;
}
vector<pair<int, int>> randomEdges(mt19937& rng, int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = rng() % n + 1, b = rng() % n + 1;
        if (a != b) edges.push_back({a, b});  // parallel edges are possible, self-loops are not used
    }
    return edges;
}
int countComponents(int n, const vector<pair<int, int>>& edges, int skipEdge, int skipVertex) {
    vector<int> leader(n + 1);
    iota(leader.begin(), leader.end(), 0);
    function<int(int)> find = [&](int x) { return leader[x] == x ? x : leader[x] = find(leader[x]); };
    for (int i = 0; i < (int)edges.size(); i++)
        if (i != skipEdge && edges[i].first != skipVertex && edges[i].second != skipVertex) leader[find(edges[i].first)] = find(edges[i].second);
    int count = 0;
    for (int v = 1; v <= n; v++)
        if (v != skipVertex && find(v) == v) count++;
    return count;
}

int main() {
    {
        auto edges = vector<pair<int, int>>{{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}, {4, 5}};
        cout << "triangle 1-2-3, edge 3-4, double edge 4-5: articulation points:";
        for (int v : findArticulationPoints(build(5, edges))) cout << ' ' << v;
        cout << "\n";
    }
    {
        auto edges = vector<pair<int, int>>{{1, 2}, {1, 3}, {1, 4}};
        cout << "a star with centre 1 (walk starts at the centre): articulation points:";
        for (int v : findArticulationPoints(build(4, edges))) cout << ' ' << v;
        cout << "\n";
    }
    {
        auto edges = vector<pair<int, int>>{{1, 2}, {2, 3}, {3, 4}, {4, 1}};
        cout << "a square: " << findArticulationPoints(build(4, edges)).size() << " articulation points\n";
    }
    // Check against the definition: remove each vertex and count the components.
    mt19937 rng(4703);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 9 + 1, m = rng() % 14;
        auto edges = randomEdges(rng, n, m);
        vector<int> expected;
        int base = countComponents(n, edges, -1, -1);
        for (int v = 1; v <= n; v++)
            if (countComponents(n, edges, -1, v) > base) expected.push_back(v);
        if (findArticulationPoints(build(n, edges)) != expected) return 1;
    }
}
