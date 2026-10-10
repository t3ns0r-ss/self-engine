/*
Problem: network of cables (CSES 1675 style).
Input: n m, then m lines "a b c": a cable between computers a and b would cost c (1 <= c <= 10^9; cables may repeat).
Output: the least total cost that connects all computers, or IMPOSSIBLE.
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
// Theorem 4.4.4. Kruskal on vertices 1..n: the weight of a minimum spanning tree, or -1 if the graph is not connected.
long long cheapestNetwork(int n, vector<array<long long, 3>> cables) {
    sort(cables.begin(), cables.end(), [](const auto& x, const auto& y) { return x[2] < y[2]; });
    Dsu dsu(n + 1);
    long long total = 0;
    int taken = 0;
    for (auto [a, b, c] : cables)
        if (dsu.unite(a, b)) total += c, taken++;
    return taken == n - 1 ? total : -1;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> cables(m);
    for (auto& c : cables) cin >> c[0] >> c[1] >> c[2];
    long long total = cheapestNetwork(n, cables);
    if (total < 0) cout << "IMPOSSIBLE\n";
    else cout << total << "\n";
}
