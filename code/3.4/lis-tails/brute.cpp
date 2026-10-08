// Brute force: every subsequence as a bitmask, checked for the order.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    int best = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        int prev = 0, len = 0;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (!((mask >> i) & 1)) continue;
            if (len > 0 && (t == 0 ? a[i] <= prev : a[i] < prev)) ok = false;
            prev = a[i];
            len++;
        }
        if (ok) best = max(best, len);
    }
    cout << best << "\n";
}
