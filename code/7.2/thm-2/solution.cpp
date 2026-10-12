#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> randomDag(int n, mt19937& rng, int percent) {
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin(), label.end(), rng);
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if ((int)(rng() % 100) < percent) edges.push_back({label[i], label[j]});
    return edges;
}

const long long MOD = 1000000007;
// snippet:begin
// Theorem 7.2.2. paths[v] = the number of paths from the vertex 0 to v (mod 1e9+7): the paths into v end with an edge u -> v.
// cheapest[v] and ways[v] = the least total weight of a path from 0 to v, and the number of paths with that weight.
struct PathCounts {
    vector<long long> paths, cheapest, ways;
    PathCounts(const vector<vector<pair<int, int>>>& out, const vector<int>& order) {  // out[v] = {(u, weight)}
        int n = out.size();
        paths.assign(n, 0), cheapest.assign(n, LLONG_MAX), ways.assign(n, 0);
        paths[0] = ways[0] = 1, cheapest[0] = 0;
        for (int v : order) {
            if (cheapest[v] == LLONG_MAX) continue;  // not reachable from 0
            for (auto [u, w] : out[v]) {
                paths[u] = (paths[u] + paths[v]) % MOD;
                if (cheapest[v] + w < cheapest[u]) cheapest[u] = cheapest[v] + w, ways[u] = ways[v];
                else if (cheapest[v] + w == cheapest[u]) ways[u] = (ways[u] + ways[v]) % MOD;
            }
        }
    }
};
// snippet:end

vector<int> kahn(const vector<vector<pair<int, int>>>& out) {
    int n = out.size();
    vector<int> indeg(n, 0), order;
    for (int v = 0; v < n; v++)
        for (auto [u, w] : out[v]) indeg[u]++;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) order.push_back(v);
    for (size_t i = 0; i < order.size(); i++)
        for (auto [u, w] : out[order[i]])
            if (--indeg[u] == 0) order.push_back(u);
    return order;
}

int main() {
    vector<vector<pair<int, int>>> out(6);
    for (auto [a, b, w] : vector<array<int, 3>>{{0, 1, 2}, {0, 2, 1}, {1, 3, 1}, {2, 3, 2}, {3, 4, 1}, {2, 5, 5}}) out[a].push_back({b, w});
    PathCounts pc(out, kahn(out));
    cout << "number of paths from 0:";
    for (long long x : pc.paths) cout << " " << x;
    cout << "\ncheapest weight:";
    for (long long x : pc.cheapest) cout << " " << x;
    cout << "\nnumber of cheapest paths:";
    for (long long x : pc.ways) cout << " " << x;
    cout << "\n";
    // Check (not printed): the same as listing all paths from the vertex 0, for 3000 random DAGs of up to 8 vertices with weights 1 to 4.
    mt19937 rng(9);
    for (int it = 0; it < 3000; it++) {
        int n = 1 + rng() % 8;
        auto edges = randomDag(n, rng, 40);
        vector<vector<pair<int, int>>> g(n);
        for (auto [a, b] : edges) g[a].push_back({b, 1 + (int)(rng() % 4)});
        PathCounts p(g, kahn(g));
        vector<long long> count(n, 0), best(n, LLONG_MAX), number(n, 0);
        function<void(int, long long)> go = [&](int v, long long cost) {
            count[v]++;
            if (cost < best[v]) best[v] = cost, number[v] = 1;
            else if (cost == best[v]) number[v]++;
            for (auto [u, w] : g[v]) go(u, cost + w);
        };
        go(0, 0);
        for (int v = 0; v < n; v++) {
            if (count[v] != p.paths[v]) return 1;
            if (count[v] > 0 && (best[v] != p.cheapest[v] || number[v] != p.ways[v])) return 1;
            if (count[v] == 0 && p.cheapest[v] != LLONG_MAX) return 1;
        }
    }
}
