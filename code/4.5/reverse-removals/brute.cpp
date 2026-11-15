#include <bits/stdc++.h>
using namespace std;

// After every collapse, test every pair of islands with a walk over the bridges that are left.
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    for (int removed = 1; removed <= m; removed++) {
        long long cut = 0;
        for (int s = 1; s <= n; s++) {
            vector<bool> seen(n + 1, false);
            vector<int> stack = {s};
            seen[s] = true;
            while (!stack.empty()) {
                int u = stack.back();
                stack.pop_back();
                for (int j = removed; j < m; j++) {
                    int v = edges[j].first == u ? edges[j].second : (edges[j].second == u ? edges[j].first : 0);
                    if (v && !seen[v]) seen[v] = true, stack.push_back(v);
                }
            }
            for (int t = s + 1; t <= n; t++) cut += !seen[t];
        }
        cout << cut << "\n";
    }
}
