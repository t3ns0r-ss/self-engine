#include <bits/stdc++.h>
using namespace std;

// Brute force: try all 2^n ways to choose the sides.
int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    vector<array<long long, 3>> pairs(m);
    for (auto& p : pairs) { cin >> p[0] >> p[1] >> p[2]; p[0]--; p[1]--; }
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {  // bit i set: item i is on side S
        long long cost = 0;
        for (int i = 0; i < n; i++) cost += (mask >> i & 1) ? a[i] : b[i];
        for (auto& p : pairs)
            if ((mask >> p[0] & 1) && !(mask >> p[1] & 1)) cost += p[2];
        best = min(best, cost);
    }
    cout << best << "\n";
}
