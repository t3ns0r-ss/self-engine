#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<pair<int, int>>>;
using Digraph = vector<vector<int>>;

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

// Theorem 4.7.2. The edge from a vertex to its parent is a bridge exactly when low[v] > tin[parent]; non-tree edges are never bridges.
vector<int> findBridges(const Graph& adj) {
    LowLink L(adj);
    vector<int> bridges;
    for (int v = 1; v < (int)adj.size(); v++)
        if (L.parent[v] && L.low[v] > L.tin[L.parent[v]]) bridges.push_back(L.parentEdge[v]);
    sort(bridges.begin(), bridges.end());
    return bridges;
}

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

// Theorem 4.7.5 (Kosaraju). walk lists the unseen vertices reachable from s in finishing order: pass 1 on the graph, pass 2 on the reversed graph.
vector<int> walk(const Digraph& g, int s, vector<bool>& seen) {
    vector<int> done;
    vector<pair<int, int>> stack = {{s, 0}};  // (vertex, how many of its edges were looked at)
    seen[s] = true;
    while (!stack.empty()) {
        auto [v, i] = stack.back();
        if (i == (int)g[v].size()) done.push_back(v), stack.pop_back();
        else {
            stack.back().second++;
            if (!seen[g[v][i]]) seen[g[v][i]] = true, stack.push_back({g[v][i], 0});
        }
    }
    return done;
}
vector<int> stronglyConnected(const Digraph& adj, int& count) {
    int n = adj.size() - 1;
    Digraph rev(n + 1);
    for (int v = 1; v <= n; v++) for (int to : adj[v]) rev[to].push_back(v);
    vector<bool> seen(n + 1, false);
    vector<int> finish, comp(n + 1, 0);
    for (int s = 1; s <= n; s++) if (!seen[s]) for (int v : walk(adj, s, seen)) finish.push_back(v);
    seen.assign(n + 1, false), count = 0;
    for (int i = n - 1; i >= 0; i--) {  // the vertex that finished last first; each walk is one component, numbered 1, 2, ... as found
        if (seen[finish[i]]) continue;
        count++;
        for (int v : walk(rev, finish[i], seen)) comp[v] = count;
    }
    return comp;
}

bool reachesEverything(const Digraph& adj, int s) {
    int count;
    auto comp = stronglyConnected(adj, count);
    vector<bool> entered(count + 1, false);
    for (int v = 1; v < (int)adj.size(); v++)
        for (int to : adj[v])
            if (comp[v] != comp[to]) entered[comp[to]] = true;  // an edge between two different components
    for (int c = 1; c <= count; c++)
        if (!entered[c] && c != comp[s]) return false;  // another source that s cannot reach
    return !entered[comp[s]];
}

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

// Test helpers: random directed graphs and the reachability table by Floyd-Warshall.
Digraph randomDigraph(mt19937& rng, int n, int m) {
    Digraph adj(n + 1);
    for (int i = 0; i < m; i++) adj[rng() % n + 1].push_back(rng() % n + 1);
    return adj;
}
vector<vector<bool>> reachability(const Digraph& adj) {
    int n = adj.size() - 1;
    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
    for (int v = 1; v <= n; v++) {
        reach[v][v] = true;
        for (int to : adj[v]) reach[v][to] = true;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;
    return reach;
}

int bridgesBrute(int n, const vector<pair<int, int>>& edges) {
    int base = countComponents(n, edges, -1, -1), count = 0;
    for (int i = 0; i < (int)edges.size(); i++) count += countComponents(n, edges, i, -1) > base;
    return count;
}
// How many roads make some two towns farther apart (or disconnected) when closed alone? Distances by Floyd-Warshall.
int slowerBrute(int n, const vector<pair<int, int>>& edges) {
    const int INF = 1000;
    auto distances = [&](int skip) {
        vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));
        for (int v = 1; v <= n; v++) d[v][v] = 0;
        for (int i = 0; i < (int)edges.size(); i++)
            if (i != skip) d[edges[i].first][edges[i].second] = d[edges[i].second][edges[i].first] = 1;
        for (int k = 1; k <= n; k++)
            for (int a = 1; a <= n; a++)
                for (int b = 1; b <= n; b++) d[a][b] = min(d[a][b], d[a][k] + d[k][b]);
        return d;
    };
    auto whole = distances(-1);
    int count = 0;
    for (int i = 0; i < (int)edges.size(); i++) {
        auto cut = distances(i);
        bool slower = false;
        for (int a = 1; a <= n; a++)
            for (int b = 1; b <= n; b++) slower = slower || cut[a][b] > whole[a][b];
        count += slower;
    }
    return count;
}
int main() {
    // P1: roads 1-2, 2-3, 3-1, 3-4, 4-5: how many roads disconnect the network when closed alone? Brute force: close each one.
    {
        vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}};
        cout << "P1 brute=" << bridgesBrute(5, edges) << " method=" << findBridges(build(5, edges)).size() << "\n";
    }
    // P2: a ring of five towns with a chord: no bridge.
    {
        vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 1}, {1, 3}};
        cout << "P2 brute=" << bridgesBrute(5, edges) << " method=" << findBridges(build(5, edges)).size() << "\n";
    }
    // N1: roads 1-2, 2-3, 3-1, 3-4: how many roads make some two towns farther apart when closed alone? Every road does, not only the bridge.
    {
        vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {3, 1}, {3, 4}};
        cout << "N1 brute=" << slowerBrute(4, edges) << " method=" << findBridges(build(4, edges)).size() << "\n";
    }
}
