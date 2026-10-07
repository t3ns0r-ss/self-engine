// Tries every subset of days to cover with passes; the passes needed are ceil(covered / D) batches.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, d;
    long long p;
    cin >> n >> d >> p;
    vector<long long> f(n);
    for (auto& x : f) cin >> x;
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long cost = 0;
        int covered = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) covered++;
            else cost += f[i];
        }
        cost += (long long)((covered + d - 1) / d) * p;
        best = min(best, cost);
    }
    cout << best << "\n";
}
