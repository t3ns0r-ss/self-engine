#include <bits/stdc++.h>
using namespace std;

const int N = 6;
long long cap[N][N];  // residual capacities

// snippet:begin
// Theorem 7.9.3. One round of Edmonds-Karp: find a path with the fewest edges among the edges of positive residual
// capacity (breadth-first search) and push the largest possible amount along it.
// Returns the number of edges of that path, or -1 when there is no augmenting path left.
int augmentOnce(int s, int t) {
    int parent[N], dist[N];
    fill(parent, parent + N, -1);
    parent[s] = s;
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < N; v++)
            if (parent[v] < 0 && cap[u][v] > 0) { parent[v] = u; dist[v] = dist[u] + 1; q.push(v); }
    }
    if (parent[t] < 0) return -1;
    long long push = LLONG_MAX;
    for (int v = t; v != s; v = parent[v]) push = min(push, cap[parent[v]][v]);
    for (int v = t; v != s; v = parent[v]) { cap[parent[v]][v] -= push; cap[v][parent[v]] += push; }
    return dist[t];
}
// snippet:end

void load(initializer_list<array<long long, 3>> edges) {
    memset(cap, 0, sizeof cap);
    for (auto e : edges) cap[e[0]][e[1]] += e[2];
}

// Runs Edmonds-Karp to the end; returns the lengths of the augmenting paths in order.
vector<int> run(int s, int t) {
    vector<int> lengths;
    while (true) {
        int len = augmentOnce(s, t);
        if (len < 0) return lengths;
        lengths.push_back(len);
    }
}

void print(const char* name, const vector<int>& lengths, int edges, int vertices) {
    cout << name << ": path lengths";
    for (int len : lengths) cout << " " << len;
    cout << " (rounds: " << lengths.size() << ", bound V*E: " << vertices * edges << ")\n";
}

int main() {
    // Example 1: the cross edge a -> b with capacity 1 between two wide paths. Vertices s = 0, a = 1, b = 2, t = 3.
    load({{0, 1, 1000}, {0, 2, 1000}, {1, 2, 1}, {1, 3, 1000}, {2, 3, 1000}});
    print("wide paths", run(0, 3), 5, 4);
    // The same network, always augmenting through the cross edge: s,a,b,t and then s,b,a,t push 1 each time.
    load({{0, 1, 1000}, {0, 2, 1000}, {1, 2, 1}, {1, 3, 1000}, {2, 3, 1000}});
    auto along = [&](vector<int> path) {
        long long push = LLONG_MAX;
        for (size_t i = 0; i + 1 < path.size(); i++) push = min(push, cap[path[i]][path[i + 1]]);
        for (size_t i = 0; i + 1 < path.size(); i++) { cap[path[i]][path[i + 1]] -= push; cap[path[i + 1]][path[i]] += push; }
        return push;
    };
    long long flow = 0;
    int rounds = 0;
    while (flow < 2000) { flow += along({0, 1, 2, 3}); flow += along({0, 2, 1, 3}); rounds += 2; }
    cout << "always through the cross edge: " << rounds << " rounds to reach flow " << flow << "\n";
    // Example 2: six vertices. s = 0, t = 5.
    load({{0, 1, 1}, {0, 2, 1}, {1, 3, 1}, {2, 3, 1}, {3, 4, 2}, {4, 5, 2}, {1, 5, 1}});
    print("six vertices", run(0, 5), 7, 6);
    // Example 3: a chain of three edges.
    load({{0, 1, 3}, {1, 2, 2}, {2, 3, 4}});
    print("a chain", run(0, 3), 3, 4);

    // Check on every graph on 4 vertices with capacities 0, 1 or 2: path lengths never decrease, and there are at most V * E rounds.
    int pairs[12][2], k = 0;
    for (int u = 0; u < 4; u++)
        for (int v = 0; v < 4; v++)
            if (u != v) { pairs[k][0] = u; pairs[k][1] = v; k++; }
    long long total = 1;
    for (int i = 0; i < 12; i++) total *= 3;
    for (long long code = 0; code < total; code++) {
        long long c = code;
        memset(cap, 0, sizeof cap);
        int edges = 0;
        for (int i = 0; i < 12; i++) { cap[pairs[i][0]][pairs[i][1]] = c % 3; edges += c % 3 > 0; c /= 3; }
        vector<int> lengths = run(0, 3);
        if (!is_sorted(lengths.begin(), lengths.end())) return 1;
        if ((int)lengths.size() > 4 * edges) return 1;
    }
}
