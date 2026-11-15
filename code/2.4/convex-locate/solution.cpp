#include <bits/stdc++.h>
using namespace std;

/*
Problem: a strictly convex polygon (every angle below 180 degrees), corners in counterclockwise order, and q query points.
For each point say whether it is inside, outside or on the boundary. Coordinates up to 10^9 in absolute value, n and q up to 2*10^5.
Input: n, n lines x y, then q, then q lines x y.
Output: for each query IN, OUT or ON.
*/

// snippet:begin
struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
bool inBox(Point a, Point b, Point q) {
    return min(a.x, b.x) <= q.x && q.x <= max(a.x, b.x) && min(a.y, b.y) <= q.y && q.y <= max(a.y, b.y);
}
// 0 outside, 1 on the boundary, 2 inside. The rays from p[0] to the other corners come in counterclockwise order, so a
// binary search finds the triangle p[0], p[lo], p[lo + 1] that holds q.
int locateConvex(const vector<Point>& p, Point q) {
    int n = p.size();
    long long toFirst = cross(p[0], p[1], q), toLast = cross(p[0], p[n - 1], q);
    if (toFirst < 0 || toLast > 0) return 0;                                   // outside the angle at p[0]
    if (toFirst == 0) return inBox(p[0], p[1], q) ? 1 : 0;                      // on the line of the first edge
    if (toLast == 0) return inBox(p[0], p[n - 1], q) ? 1 : 0;                   // on the line of the last edge
    int lo = 1, hi = n - 1;  // q is left of p[0] -> p[lo] and right of p[0] -> p[hi]
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        if (cross(p[0], p[mid], q) > 0) lo = mid;
        else hi = mid;
    }
    long long side = cross(p[lo], p[hi], q);  // the far edge of the triangle decides
    return side > 0 ? 2 : (side == 0 ? 1 : 0);
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n;
    vector<Point> p(n);
    for (auto& c : p) cin >> c.x >> c.y;
    cin >> q;
    while (q--) {
        Point c;
        cin >> c.x >> c.y;
        int r = locateConvex(p, c);
        cout << (r == 0 ? "OUT" : (r == 1 ? "ON" : "IN")) << "\n";
    }
}
