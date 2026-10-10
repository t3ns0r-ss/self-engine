#include <bits/stdc++.h>
using namespace std;

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n, q;
        cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;
        cin >> q;
        while (q--) {
            int l, k;
            cin >> l >> k;
            int v = a[l - 1], best = -1;
            for (int r = l - 1; r < n; r++) {
                if (r > l - 1) v &= a[r];
                if (v >= k) best = r + 1;
            }
            cout << best << (q ? ' ' : '\n');
        }
    }
}
