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
    long long best = LLONG_MIN;
    for (int s = 0; s < n; s++) {
        function<void(int, int, long long)> go = [&](int v, int p, long long sum) {
            sum += w[v];
            best = max(best, sum);
            for (int u : adj[v])
                if (u != p) go(u, v, sum);
        };
        go(s, -1, 0);
    }
    cout << best << "\n";
}
