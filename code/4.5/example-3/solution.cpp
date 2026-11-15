/*
Problem: LeetCode 1584, Min Cost to Connect All Points.
Input: n, then n lines "x y". Connecting two points costs |x1 - x2| + |y1 - y2|.
Output: the least total cost that makes all points connected.
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
// Example 3. Kruskal on the complete graph of the points: list every link, sort by cost, keep a link when it joins two groups.
int minCostConnectPoints(const vector<vector<int>>& points) {
    int n = points.size();
    vector<array<int, 3>> links;
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++)
            links.push_back({abs(points[a][0] - points[b][0]) + abs(points[a][1] - points[b][1]), a, b});
    sort(links.begin(), links.end());  // by cost first
    Dsu dsu(n);
    int total = 0;
    for (auto [cost, a, b] : links)
        if (dsu.unite(a, b)) total += cost;
    return total;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<int>> points(n, vector<int>(2));
    for (auto& p : points) cin >> p[0] >> p[1];
    cout << minCostConnectPoints(points) << "\n";
}
