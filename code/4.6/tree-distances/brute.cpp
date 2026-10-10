#include <bits/stdc++.h>
using namespace std;

// A walk from a for every query.
int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> edges(n - 1);
    for (auto& e : edges) cin >> e.first >> e.second;
    while (q--) {
        int a, b;
        cin >> a >> b;
        vector<int> dist(n + 1, -1);
        dist[a] = 0;
        vector<int> stack = {a};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (auto [x, y] : edges) {
                int v = x == u ? y : (y == u ? x : 0);
                if (v && dist[v] < 0) dist[v] = dist[u] + 1, stack.push_back(v);
            }
        }
        cout << dist[b] << "\n";
    }
}
