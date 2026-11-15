#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> coins(n);
    for (auto& x : coins) cin >> x;
    vector<vector<int>> out(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a - 1].push_back(b - 1);
    }
    vector<char> seen(n << n, 0);
    long long best = 0;
    vector<pair<int, int>> stack;
    for (int s = 0; s < n; s++) stack.push_back({s, 1 << s}), seen[s << n | 1 << s] = 1;
    while (!stack.empty()) {
        auto [v, mask] = stack.back();
        stack.pop_back();
        long long sum = 0;
        for (int u = 0; u < n; u++)
            if (mask >> u & 1) sum += coins[u];
        best = max(best, sum);
        for (int u : out[v]) {
            int m2 = mask | 1 << u;
            if (!seen[u << n | m2]) seen[u << n | m2] = 1, stack.push_back({u, m2});
        }
    }
    cout << best << "\n";
}
