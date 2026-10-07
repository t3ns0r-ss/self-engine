// Tries every subarray; for every i scans all other elements.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long best = LLONG_MIN;
    for (int l = 0; l < n; l++) {
        long long s = 0;
        for (int r = l; r < n; r++) {
            s += a[r];
            best = max(best, s);
        }
    }
    cout << best << "\n";
    for (int i = 0; i < n; i++) {
        long long m = LLONG_MIN;
        for (int j = 0; j < n; j++)
            if (j != i) m = max(m, a[j]);
        cout << m << (i + 1 < n ? ' ' : '\n');
    }
}
