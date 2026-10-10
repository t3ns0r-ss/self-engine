/*
Problem: on an infinite grid, can a walker go from (sx, sy) to (tx, ty) in exactly t steps,
each step to one of the 4 side neighbours?
Input: q, then q lines "sx sy tx ty t" (|coordinates| <= 10^9, 0 <= t <= 10^18).
Output: YES or NO per query.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.4.3. Can a walker go from (sx, sy) to (tx, ty) in exactly t side steps? Each step flips the parity
// of x + y, so t and the distance d must have the same parity, and d <= t.
bool exactSteps(long long sx, long long sy, long long tx, long long ty, long long t) {
    long long d = llabs(tx - sx) + llabs(ty - sy);
    return d <= t && (t - d) % 2 == 0;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        long long sx, sy, tx, ty, t;
        cin >> sx >> sy >> tx >> ty >> t;
        cout << (exactSteps(sx, sy, tx, ty, t) ? "YES" : "NO") << "\n";
    }
}
