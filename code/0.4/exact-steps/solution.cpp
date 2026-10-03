/*
Problem: on an infinite grid, can a walker go from (sx, sy) to (tx, ty) in exactly t steps,
each step to one of the 4 side neighbours?
Input: q, then q lines "sx sy tx ty t" (|coordinates| <= 10^9, 0 <= t <= 10^18).
Output: YES or NO per query.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        long long sx, sy, tx, ty, t;
        cin >> sx >> sy >> tx >> ty >> t;
        long long d = llabs(tx - sx) + llabs(ty - sy);  // fewest steps; up to 4*10^9
        // each step flips the parity of x + y, so t and d must have the same parity
        bool ok = d <= t && (t - d) % 2 == 0;
        cout << (ok ? "YES" : "NO") << "\n";
    }
}
