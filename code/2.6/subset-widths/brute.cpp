#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 1000000007;
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long total = 0;
    for (int mask = 1; mask < (1 << n); mask++) {  // every non-empty subset (topic 0.5)
        long long mx = LLONG_MIN, mn = LLONG_MAX;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) mx = max(mx, a[i]), mn = min(mn, a[i]);
        total = (total + (mx - mn)) % MOD;
    }
    cout << total << "\n";
}
