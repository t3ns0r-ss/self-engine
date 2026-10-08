// Brute force: every subsequence as a bitmask, checked pair by pair.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    int best = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        long long prev = 0;
        int len = 0;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (!((mask >> i) & 1)) continue;
            if (len > 0 && llabs(a[i] - prev) > k) ok = false;
            prev = a[i];
            len++;
        }
        if (ok) best = max(best, len);
    }
    cout << best << "\n";
}
