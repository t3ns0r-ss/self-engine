// Brute force: every bitmask subset (Theorem 0.5.2).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long T;
    cin >> n >> T;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long s = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s += a[i];
        if (s <= T) best = max(best, s);
    }
    cout << best << "\n";
}
