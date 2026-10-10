/*
Problem: connecting all points.
Input: n, then n lines "x y": points in the plane (|x|, |y| <= 10^6; points may coincide). Connecting two points costs
|x1 - x2| + |y1 - y2|.
Output: the least total cost that makes all points connected.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.4.5. Prim without a heap on the complete graph: the weight of a minimum spanning tree of the points.
long long cheapestNetworkOfPoints(const vector<pair<long long, long long>>& p) {
    int n = p.size();
    const long long INF = LLONG_MAX / 4;
    vector<long long> best(n, INF);  // the cheapest link from a point outside the tree to the tree
    vector<bool> inTree(n, false);
    best[0] = 0;
    long long total = 0;
    for (int step = 0; step < n; step++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!inTree[v] && (u == -1 || best[v] < best[u])) u = v;  // the point outside that is cheapest to join
        inTree[u] = true;
        total += best[u];
        for (int v = 0; v < n; v++)
            if (!inTree[v]) best[v] = min(best[v], llabs(p[u].first - p[v].first) + llabs(p[u].second - p[v].second));
    }
    return total;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> p(n);
    for (auto& q : p) cin >> q.first >> q.second;
    cout << cheapestNetworkOfPoints(p) << "\n";
}
