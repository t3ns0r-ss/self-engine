// Tries every subset.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long T;
    cin >> n >> T;
    vector<long long> v(n);
    for (auto& x : v) cin >> x;
    int best = INT_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long s = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) s += v[i];
        if (s >= T) best = min(best, __builtin_popcount(mask));
    }
    cout << (best == INT_MAX ? -1 : best) << "\n";
}
