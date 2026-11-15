#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.8.2. Do the closed segments ab and cd share a point? (a != b, c != d)
struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
int sign(long long v) { return (v > 0) - (v < 0); }  // the sign, so that no product of two big numbers is formed
bool inBox(Point a, Point b, Point p) {  // p is inside the bounding box of ab (with cross = 0: p is on the segment ab)
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}
bool segmentsMeet(Point a, Point b, Point c, Point d) {
    int d1 = sign(cross(a, b, c)), d2 = sign(cross(a, b, d));  // sides of c and d seen from ab
    int d3 = sign(cross(c, d, a)), d4 = sign(cross(c, d, b));  // sides of a and b seen from cd
    if (d1 * d2 < 0 && d3 * d4 < 0) return true;                // the segments cross properly
    return (d1 == 0 && inBox(a, b, c)) || (d2 == 0 && inBox(a, b, d)) ||  // an end of one lies on the other
           (d3 == 0 && inBox(c, d, a)) || (d4 == 0 && inBox(c, d, b));
}
// snippet:end

// Reference by a different method: solve a + t*(b-a) = c + u*(d-c) exactly for t and u, with 0 <= t, u <= 1.
bool meetBySolving(Point a, Point b, Point c, Point d) {
    long long rx = b.x - a.x, ry = b.y - a.y, sx = d.x - c.x, sy = d.y - c.y;
    long long den = rx * sy - ry * sx;
    long long qx = c.x - a.x, qy = c.y - a.y;
    if (den != 0) {
        long long tn = qx * sy - qy * sx, un = qx * ry - qy * rx;  // t = tn / den, u = un / den
        if (den < 0) den = -den, tn = -tn, un = -un;
        return 0 <= tn && tn <= den && 0 <= un && un <= den;
    }
    if (qx * ry - qy * rx != 0) return false;  // parallel and on different lines
    // On one line: compare the ranges along x, or along y when the line is vertical.
    long long lo1 = min(a.x, b.x), hi1 = max(a.x, b.x), lo2 = min(c.x, d.x), hi2 = max(c.x, d.x);
    if (rx == 0) lo1 = min(a.y, b.y), hi1 = max(a.y, b.y), lo2 = min(c.y, d.y), hi2 = max(c.y, d.y);
    return max(lo1, lo2) <= min(hi1, hi2);
}

int main() {
    auto show = [&](Point a, Point b, Point c, Point d, const char* note) {
        cout << "(" << a.x << "," << a.y << ")-(" << b.x << "," << b.y << ") and (" << c.x << "," << c.y << ")-(" << d.x << "," << d.y << "): "
             << (segmentsMeet(a, b, c, d) ? "yes" : "no") << " (" << note << ")\n";
    };
    show({0, 0}, {4, 4}, {0, 4}, {4, 0}, "they cross at (2,2)");
    show({0, 0}, {2, 0}, {2, 0}, {2, 3}, "they touch at the end (2,0)");
    show({0, 0}, {3, 0}, {2, 0}, {5, 0}, "on one line, overlapping on x from 2 to 3");
    show({0, 0}, {1, 0}, {2, 0}, {3, 0}, "on one line, apart: all four cross values are 0");

    vector<Point> grid;
    for (int x = 0; x <= 3; x++)
        for (int y = 0; y <= 3; y++) grid.push_back({x, y});
    for (Point a : grid)
        for (Point b : grid) {
            if (a.x == b.x && a.y == b.y) continue;
            for (Point c : grid)
                for (Point d : grid) {
                    if (c.x == d.x && c.y == d.y) continue;
                    if (segmentsMeet(a, b, c, d) != meetBySolving(a, b, c, d)) return 1;
                }
        }
}
