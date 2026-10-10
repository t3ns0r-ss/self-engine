#include <bits/stdc++.h>
using namespace std;

// A walk from a that keeps the smallest limit seen on the way to every town.
int main() {
    int n, q;
    cin >> n >> q;
    vector<array<long long, 3>> edges(n - 1);
    for (auto& e : edges) cin >> e[0] >> e[1] >> e[2];
    while (q--) {
        int a, b;
        cin >> a >> b;
        vector<long long> low(n + 1, -1);
        low[a] = LLONG_MAX;
        vector<int> stack = {a};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (auto& e : edges) {
                int v = e[0] == u ? e[1] : (e[1] == u ? e[0] : 0);
                if (v && low[v] < 0) low[v] = min(low[u], e[2]), stack.push_back(v);
            }
        }
        cout << low[b] << "\n";
    }
}
