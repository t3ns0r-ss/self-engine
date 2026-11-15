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
    long long best = 0;
    function<void(int, long long)> go = [&](int v, long long sum) {
        best = max(best, sum);
        for (auto [u, w] : out[v]) go(u, sum + w);
    };
    for (int s = 0; s < n; s++) go(s, 0);
    cout << best << "\n";
}
