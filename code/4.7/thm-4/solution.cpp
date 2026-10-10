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
// Theorem 4.7.4. Label the pieces of the walk tree left after cutting the bridges (they are the 2-edge-connected components), and
// orient every edge: tree edges downwards, back edges upwards. If the graph is connected and has no bridge, the result is strongly connected.
vector<int> edgeComponents(const Graph& adj, int& count) {
    LowLink L(adj);
    vector<int> comp(adj.size(), 0);
    count = 0;
    for (int v : L.order) {  // parents come before children
        int p = L.parent[v];
        comp[v] = (p && L.low[v] <= L.tin[p]) ? comp[p] : ++count;  // the edge above v is not a bridge: same piece as the parent
    }
    return comp;
}
vector<pair<int, int>> orientEdges(const Graph& adj, int m) {
    LowLink L(adj);
    vector<pair<int, int>> direction(m);  // (from, to) for each edge number
    for (int v = 1; v < (int)adj.size(); v++)
        for (auto [to, id] : adj[v])
            if (L.parentEdge[to] == id || (L.parentEdge[v] != id && L.tin[v] > L.tin[to])) direction[id] = {v, to};
    return direction;
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
        auto edges = vector<pair<int, int>>{{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}, {5, 6}, {6, 4}};
        int count;
        auto comp = edgeComponents(build(6, edges), count);
        cout << "two triangles joined by the edge 3-4: " << count << " components, labels:";
        for (int v = 1; v <= 6; v++) cout << ' ' << comp[v];
        cout << "\n";
    }
    {
        auto edges = vector<pair<int, int>>{{1, 2}, {2, 3}, {3, 1}};
        auto dir = orientEdges(build(3, edges), 3);
        cout << "the triangle oriented:";
        for (auto [a, b] : dir) cout << ' ' << a << "->" << b;
        cout << "\n";
    }
    {
        auto edges = vector<pair<int, int>>{{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 3}, {1, 2}};
        auto dir = orientEdges(build(4, edges), 6);
        cout << "a square with a diagonal and a double edge oriented:";
        for (auto [a, b] : dir) cout << ' ' << a << "->" << b;
        cout << "\n";
    }
    // Check against the definitions: the pieces are the components after removing the bridges (found by trying every edge), and
    // a connected graph without bridges gets a strongly connected orientation.
    mt19937 rng(4704);
    int orientedChecks = 0;
    for (int trial = 0; trial < 30000; trial++) {
        int n = rng() % 8 + 1, m = rng() % 16;
        auto edges = randomEdges(rng, n, m);
        int base = countComponents(n, edges, -1, -1);
        vector<int> leader(n + 1);
        iota(leader.begin(), leader.end(), 0);
        function<int(int)> find = [&](int x) { return leader[x] == x ? x : leader[x] = find(leader[x]); };
        bool bridgeless = true;
        for (int i = 0; i < (int)edges.size(); i++) {
            if (countComponents(n, edges, i, -1) > base) bridgeless = false;
            else leader[find(edges[i].first)] = find(edges[i].second);
        }
        int count;
        auto comp = edgeComponents(build(n, edges), count);
        for (int a = 1; a <= n; a++)
            for (int b = 1; b <= n; b++)
                if ((find(a) == find(b)) != (comp[a] == comp[b])) return 1;
        if (bridgeless && base == 1) {
            auto dir = orientEdges(build(n, edges), edges.size());
            vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
            for (int v = 1; v <= n; v++) reach[v][v] = true;
            for (int i = 0; i < (int)edges.size(); i++) {
                auto [a, b] = dir[i];
                if (!((a == edges[i].first && b == edges[i].second) || (a == edges[i].second && b == edges[i].first))) return 1;
                reach[a][b] = true;
            }
            for (int k = 1; k <= n; k++)
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        if (reach[i][k] && reach[k][j]) reach[i][j] = true;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (!reach[i][j]) return 1;
            orientedChecks++;
        }
    }
    if (orientedChecks < 200) return 1;  // the random graphs must contain enough bridgeless ones
}
