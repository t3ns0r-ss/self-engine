#include <bits/stdc++.h>
using namespace std;

// Brute force: walk along all edges (the simple test of Theorem 2.6.4, one pass per query).
struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }

int main() {
    int n, q;
    cin >> n;
    vector<Point> p(n);
    for (auto& c : p) cin >> c.x >> c.y;
    cin >> q;
    while (q--) {
        Point c;
        cin >> c.x >> c.y;
        bool on = false, outside = false;
        for (int i = 0; i < n; i++) {
            Point a = p[i], b = p[(i + 1) % n];
            long long v = cross(a, b, c);
            if (v < 0) outside = true;  // a convex polygon in counterclockwise order: inside means left of every edge
            if (v == 0 && min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y)) on = true;
        }
        puts(outside ? "OUT" : (on ? "ON" : "IN"));
    }
}
