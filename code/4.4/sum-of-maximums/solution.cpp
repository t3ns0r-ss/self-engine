/*
Problem: tolls on a tree of cities.
Input: n, then n - 1 lines "a b w": a road of toll w (1 <= w <= 10^7) between cities a and b; the roads form a tree.
The toll of a trip is the largest toll on it.
Output: the sum of the tolls of the trips between all pairs of different cities (a < b).
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
// Theorem 4.4.6. Sum over all pairs of the largest road on their trip: a road of weight w that joins groups of sizes a and b is the
// largest road on exactly a * b pairs. Cities are 1..n.
long long sumOfLargest(int n, vector<array<long long, 3>> roads) {
    sort(roads.begin(), roads.end(), [](const auto& x, const auto& y) { return x[2] < y[2]; });
    Dsu dsu(n + 1);
    long long total = 0;
    for (auto [a, b, w] : roads) {
        a = dsu.find(a), b = dsu.find(b);
        total += w * dsu.size[a] * dsu.size[b];  // the pairs that the two groups make with each other
        dsu.unite(a, b);
    }
    return total;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> roads(n - 1);
    for (auto& r : roads) cin >> r[0] >> r[1] >> r[2];
    cout << sumOfLargest(n, roads) << "\n";
}
