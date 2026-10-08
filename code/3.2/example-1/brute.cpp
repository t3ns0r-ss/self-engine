// Brute force: every one of the 2^N choices as a bitmask (Theorem 0.5.2), checked pair by pair.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    long long count = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int i = 0; i + 1 < n; i++) {
            long long x = ((mask >> i) & 1) ? b[i] : a[i];
            long long y = ((mask >> (i + 1)) & 1) ? b[i + 1] : a[i + 1];
            if (x == y) ok = false;
        }
        if (ok) count++;
    }
    cout << count % 998244353 << "\n";
}
