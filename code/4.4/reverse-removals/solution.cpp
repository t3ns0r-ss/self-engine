/*
Problem: decaying bridges.
Input: n m, then m lines "a b": a bridge between islands a and b (all bridges are distinct, a < b). The bridges collapse in the
order they are listed.
Output: m numbers: after the i-th bridge collapses, the number of pairs of islands that cannot reach each other.
*/
#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> parent, size;
    Dsu(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        while (parent[x] != x) parent[x] = parent[parent[x]], x = parent[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

// snippet:begin
// Theorem 4.4.2. The number of cut-off pairs of vertices after each of the m removals (islands 1..n), by adding the edges in reverse.
vector<long long> separatedPairs(int n, const vector<pair<int, int>>& edges) {
    int m = edges.size();
    vector<long long> answer(m + 1);
    Dsu dsu(n + 1);
    long long total = 1LL * n * (n - 1) / 2, linked = 0;  // linked: pairs that can reach each other in the graph built so far
    for (int i = m; i >= 1; i--) {
        answer[i] = total - linked;  // the graph built so far is the state after i removals
        auto [a, b] = edges[i - 1];
        a = dsu.find(a), b = dsu.find(b);
        if (a != b) linked += 1LL * dsu.size[a] * dsu.size[b], dsu.unite(a, b);  // every pair across the two groups is new
    }
    return vector<long long>(answer.begin() + 1, answer.end());
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    auto answer = separatedPairs(n, edges);
    for (int i = 0; i < m; i++) cout << answer[i] << "\n";
}
