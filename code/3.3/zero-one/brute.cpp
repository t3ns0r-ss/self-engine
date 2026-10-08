// Brute force: every subset as a bitmask (Theorem 0.5.2).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, W;
    cin >> n >> W;
    vector<long long> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    long long best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long tw = 0, tv = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) {
                tw += w[i];
                tv += v[i];
            }
        if (tw <= W) best = max(best, tv);
    }
    cout << best << "\n";
}
