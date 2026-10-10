/*
Problem: power stations or links.
Input: n m, then n numbers c_1..c_n (the price of a power station in town i), then m lines "a b w": a link of price w between
towns a and b. A town is supplied if it has a station or is connected through links to a town that has one.
Output: the least total price so that every town is supplied.
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
// Theorem 4.4.4 with a virtual town 0: a station in town i is a link {0, i} of price c[i]; a minimum spanning tree of the
// enlarged graph connects every town to some station. Towns 1..n; c has n + 1 entries (c[0] unused).
long long cheapestSupply(int n, const vector<long long>& c, vector<array<long long, 3>> links) {
    for (int i = 1; i <= n; i++) links.push_back({0, i, c[i]});  // "build a station here" is a link to the virtual town
    sort(links.begin(), links.end(), [](const auto& x, const auto& y) { return x[2] < y[2]; });
    Dsu dsu(n + 1);
    long long total = 0;
    for (auto [a, b, w] : links)
        if (dsu.unite(a, b)) total += w;
    return total;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> c(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> c[i];
    vector<array<long long, 3>> links(m);
    for (auto& l : links) cin >> l[0] >> l[1] >> l[2];
    cout << cheapestSupply(n, c, links) << "\n";
}
