#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    vector<int> ea(n - 1), eb(n - 1);
    for (int i = 0; i + 1 < n; i++) cin >> ea[i] >> eb[i], ea[i]--, eb[i]--;
    long long best = LLONG_MIN / 4;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) != k) continue;
        int first = __builtin_ctz(mask);
        vector<int> seen(n, 0), stack = {first};
        seen[first] = 1;
        int reached = 1;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            for (int i = 0; i + 1 < n; i++) {
                int u = ea[i] == v ? eb[i] : eb[i] == v ? ea[i] : -1;
                if (u >= 0 && (mask >> u & 1) && !seen[u]) seen[u] = 1, reached++, stack.push_back(u);
            }
        }
        if (reached != k) continue;
        long long sum = 0;
        for (int v = 0; v < n; v++)
            if (mask >> v & 1) sum += w[v];
        best = max(best, sum);
    }
    cout << best << "\n";
}
