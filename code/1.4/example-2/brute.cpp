// Tries every way to place k - 1 cuts in the n - 1 gaps (bitmask over the gaps).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> x(n);
    for (auto& v : x) cin >> v;
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {
        if (__builtin_popcount(mask) != k - 1) continue;
        long long cur = 0, worst = 0;
        for (int i = 0; i < n; i++) {
            cur += x[i];
            if (i == n - 1 || (mask >> i & 1)) {  // a cut after element i
                worst = max(worst, cur);
                cur = 0;
            }
        }
        best = min(best, worst);
    }
    cout << best << "\n";
}
