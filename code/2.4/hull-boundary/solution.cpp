#include <bits/stdc++.h>
using namespace std;

/*
Problem: n different points in the plane. Print every point that lies on the boundary of their convex hull, including the points
in the middle of an edge. Coordinates up to 10^9 in absolute value.
Input: n, then n lines x y.
Output: k, the number of such points, then the k points in increasing order of x (then y), one per line.
*/

// snippet:begin
struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
bool before(Point a, Point b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); }
// Every input point on the boundary of the hull, sorted. Only a right turn (cross < 0) removes a point, so points on an edge stay.
vector<Point> hullBoundary(vector<Point> pts) {
    sort(pts.begin(), pts.end(), before);
    if (pts.size() < 3) return pts;
    vector<Point> h;
    for (int pass = 0; pass < 2; pass++) {  // lower chain left to right, then upper chain right to left
        size_t start = h.size();
        for (Point p : pts) {
            while (h.size() >= start + 2 && cross(h[h.size() - 2], h.back(), p) < 0) h.pop_back();
            h.push_back(p);
        }
        h.pop_back();
        reverse(pts.begin(), pts.end());
    }
    sort(h.begin(), h.end(), before);  // a point on an edge between the two chains, or all points on one line, can appear twice
    h.erase(unique(h.begin(), h.end(), [](Point a, Point b) { return a.x == b.x && a.y == b.y; }), h.end());
    return h;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& q : p) cin >> q.x >> q.y;
    vector<Point> h = hullBoundary(p);
    cout << h.size() << "\n";
    for (Point q : h) cout << q.x << " " << q.y << "\n";
}
