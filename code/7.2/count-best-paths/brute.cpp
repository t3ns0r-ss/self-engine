#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> out(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        out[a - 1].push_back({b - 1, w});
    }
    long long best = LLONG_MAX, count = 0;
    function<void(int, long long)> go = [&](int v, long long cost) {
        if (v == n - 1) {
            if (cost < best) best = cost, count = 1;
            else if (cost == best) count++;
        }
        for (auto [u, w] : out[v]) go(u, cost + w);
    };
    go(0, 0);
    if (best == LLONG_MAX) cout << "IMPOSSIBLE\n";
    else cout << best << " " << count % 1000000007 << "\n";
}
