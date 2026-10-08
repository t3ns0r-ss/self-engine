// Brute force: every subset of projects as a bitmask, checked pair by pair for shared days.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n), p(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> p[i];
    long long best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (!((mask >> i) & 1)) continue;
            sum += p[i];
            for (int j = 0; j < i; j++)
                if (((mask >> j) & 1) && max(a[i], a[j]) <= min(b[i], b[j])) ok = false;
        }
        if (ok) best = max(best, sum);
    }
    cout << best << "\n";
}
