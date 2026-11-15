// Brute force by a different description: choose which positions of a and of b are kept and lined up in
// pairs (the same number on both sides, in order); every other character is deleted or inserted, and each
// pair of different letters costs one replacement.
#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size(), best = INT_MAX;
    for (int ma = 0; ma < (1 << n); ma++)
        for (int mb = 0; mb < (1 << m); mb++) {
            if (__builtin_popcount(ma) != __builtin_popcount(mb)) continue;
            string x, y;
            for (int i = 0; i < n; i++)
                if ((ma >> i) & 1) x += a[i];
            for (int j = 0; j < m; j++)
                if ((mb >> j) & 1) y += b[j];
            int cost = (n - (int)x.size()) + (m - (int)y.size());
            for (size_t k = 0; k < x.size(); k++) cost += (x[k] != y[k]);
            best = min(best, cost);
        }
    cout << best << "\n";
}
