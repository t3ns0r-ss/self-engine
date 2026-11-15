#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    vector<vector<int>> adj(n);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1), adj[b - 1].push_back(a - 1);
    }
    for (int r = 0; r < n; r++) {
        function<long long(int, int)> go = [&](int v, int p) {
            long long x = w[v];
            for (int u : adj[v])
                if (u != p) x += max(0LL, go(u, v));
            return x;
        };
        cout << go(r, -1) << (r + 1 < n ? " " : "\n");
    }
}
