#include <bits/stdc++.h>
using namespace std;

/*
Problem: t pairs of segments with integer ends up to 10^9 in absolute value. Say whether the two segments of each pair share a point.
Input: t, then t lines x1 y1 x2 y2 x3 y3 x4 y4 (the first segment ends at (x1,y1) and (x2,y2), the second at (x3,y3) and (x4,y4)).
Output: for each pair YES or NO. Touching and overlapping count as sharing a point.
*/

// snippet:begin
struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
int sign(long long v) { return (v > 0) - (v < 0); }
// The compact test: the bounding boxes overlap, and each segment has the ends of the other on its line or on opposite sides of it.
bool segmentsMeet(Point a, Point b, Point c, Point d) {
    if (max(min(a.x, b.x), min(c.x, d.x)) > min(max(a.x, b.x), max(c.x, d.x))) return false;  // the x ranges are apart
    if (max(min(a.y, b.y), min(c.y, d.y)) > min(max(a.y, b.y), max(c.y, d.y))) return false;  // the y ranges are apart
    return sign(cross(a, b, c)) * sign(cross(a, b, d)) <= 0 && sign(cross(c, d, a)) * sign(cross(c, d, b)) <= 0;
}
// snippet:end

int main() {
    int t;
    cin >> t;
    while (t--) {
        Point a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        cout << (segmentsMeet(a, b, c, d) ? "YES" : "NO") << "\n";
    }
}
