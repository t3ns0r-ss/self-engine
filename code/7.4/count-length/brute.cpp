#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    long long count = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) != t) continue;
        int last = INT_MIN;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) ok &= last < a[i], last = a[i];
        count += ok;
    }
    cout << count % 1'000'000'007 << "\n";
}
