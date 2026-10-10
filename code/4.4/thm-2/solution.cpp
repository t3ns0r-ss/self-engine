#include <bits/stdc++.h>
using namespace std;

// The structure of Theorem 4.4.1.
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
// Theorem 4.4.2. Edges 0..m-1 (pairs of vertices 0..n-1) are removed in this order. Returns the number of groups of vertices
// after 0, 1, ..., m removals, by adding the edges back in reverse order.
vector<int> groupsAfterRemovals(int n, const vector<pair<int, int>>& edges) {
    int m = edges.size();
    vector<int> groups(m + 1);
    Dsu dsu(n);
    int count = n;  // nothing is left after all m removals: n groups
    for (int i = m; i >= 1; i--) {
        groups[i] = count;  // the state after i removals: edges i..m-1 are present, and they have all been added
        if (dsu.unite(edges[i - 1].first, edges[i - 1].second)) count--;  // add edge i-1 back: the state after i-1 removals
    }
    groups[0] = count;
    return groups;
}
// snippet:end

int main() {
    auto show = [](const vector<int>& g) {
        string s;
        for (int x : g) s += to_string(x) + " ";
        return s;
    };
    cout << "path 0-1-2, edges 0-1 then 1-2: " << show(groupsAfterRemovals(3, {{0, 1}, {1, 2}})) << "\n";
    cout << "triangle, edges 0-1, 1-2, 0-2: " << show(groupsAfterRemovals(3, {{0, 1}, {1, 2}, {0, 2}})) << "\n";
    cout << "no edges on 2 vertices: " << show(groupsAfterRemovals(2, {})) << "\n";
    // Check against: after each removal, count the groups again by a walk over the edges that are left.
    mt19937 rng(4402);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 7 + 1, m = n > 1 ? rng() % 9 : 0;
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; i++) edges.push_back({(int)(rng() % n), (int)(rng() % n)});
        auto got = groupsAfterRemovals(n, edges);
        for (int removed = 0; removed <= m; removed++) {
            vector<int> label(n);
            iota(label.begin(), label.end(), 0);
            for (bool changed = true; changed;) {
                changed = false;
                for (int i = removed; i < m; i++) {
                    int a = label[edges[i].first], b = label[edges[i].second];
                    if (a != b) {
                        int lo = min(a, b);
                        for (int& x : label) if (x == a || x == b) x = lo;
                        changed = true;
                    }
                }
            }
            set<int> distinct(label.begin(), label.end());
            if ((int)distinct.size() != got[removed]) return 1;
        }
    }
}
