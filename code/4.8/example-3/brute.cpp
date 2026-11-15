#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    auto pieces = [&](int skip) {
        vector<int> leader(n);
        iota(leader.begin(), leader.end(), 0);
        function<int(int)> find = [&](int x) { return leader[x] == x ? x : leader[x] = find(leader[x]); };
        for (int i = 0; i < m; i++)
            if (i != skip) leader[find(edges[i].first)] = find(edges[i].second);
        int count = 0;
        for (int v = 0; v < n; v++) count += find(v) == v;
        return count;
    };
    int base = pieces(-1);
    for (int i = 0; i < m; i++)
        if (pieces(i) > base) cout << edges[i].first << " " << edges[i].second << "\n";
}
