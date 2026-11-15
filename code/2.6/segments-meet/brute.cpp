#include <bits/stdc++.h>
using namespace std;

// Brute force: solve a + t (b - a) = c + u (d - c) exactly and check 0 <= t, u <= 1; on one line compare the ranges.
int main() {
    int t;
    cin >> t;
    while (t--) {
        long long ax, ay, bx, by, cx, cy, dx, dy;
        cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;
        long long rx = bx - ax, ry = by - ay, sx = dx - cx, sy = dy - cy;
        long long den = rx * sy - ry * sx, qx = cx - ax, qy = cy - ay;
        bool meet;
        if (den != 0) {
            long long tn = qx * sy - qy * sx, un = qx * ry - qy * rx;
            if (den < 0) den = -den, tn = -tn, un = -un;
            meet = 0 <= tn && tn <= den && 0 <= un && un <= den;
        } else if (qx * ry - qy * rx != 0) {
            meet = false;
        } else {
            long long lo1 = min(ax, bx), hi1 = max(ax, bx), lo2 = min(cx, dx), hi2 = max(cx, dx);
            if (rx == 0) lo1 = min(ay, by), hi1 = max(ay, by), lo2 = min(cy, dy), hi2 = max(cy, dy);
            meet = max(lo1, lo2) <= min(hi1, hi2);
        }
        cout << (meet ? "YES" : "NO") << "\n";
    }
}
