#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.8.5. The corners of the convex hull in counterclockwise order, starting at the leftmost (lowest if tied) point.
// A point in the middle of an edge is not a corner: the test cross <= 0 removes it.
struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
vector<Point> hull(vector<Point> pts) {
    sort(pts.begin(), pts.end(), [](Point a, Point b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); });
    pts.erase(unique(pts.begin(), pts.end(), [](Point a, Point b) { return a.x == b.x && a.y == b.y; }), pts.end());
    if (pts.size() < 2) return pts;
    vector<Point> h;
    for (int pass = 0; pass < 2; pass++) {  // pass 0: the lower chain, left to right; pass 1: the upper chain, right to left
        size_t start = h.size();
        for (Point p : pts) {
            while (h.size() >= start + 2 && cross(h[h.size() - 2], h.back(), p) <= 0) h.pop_back();
            h.push_back(p);
        }
        h.pop_back();  // the last point of a chain is the first point of the next one
        reverse(pts.begin(), pts.end());
    }
    return h;
}
// snippet:end

// Reference: a point is a corner exactly when it is not in the convex hull of the other points. In the plane it is enough to
// try every segment and every triangle of the other points (the area of the triangle equals the sum of the three areas
// that p makes with its sides, when p is in it).
bool isCorner(const vector<Point>& s, size_t k) {
    Point p = s[k];
    auto area2 = [&](Point a, Point b, Point c) { return llabs(cross(a, b, c)); };
    for (size_t i = 0; i < s.size(); i++) {
        if (i == k) continue;
        for (size_t j = i + 1; j < s.size(); j++) {
            if (j == k) continue;
            if (cross(s[i], s[j], p) == 0 && min(s[i].x, s[j].x) <= p.x && p.x <= max(s[i].x, s[j].x) && min(s[i].y, s[j].y) <= p.y &&
                p.y <= max(s[i].y, s[j].y))
                return false;
            for (size_t l = j + 1; l < s.size(); l++) {
                if (l == k) continue;
                long long whole = area2(s[i], s[j], s[l]);
                if (whole != 0 && whole == area2(p, s[i], s[j]) + area2(p, s[j], s[l]) + area2(p, s[l], s[i])) return false;
            }
        }
    }
    return true;
}

int main() {
    auto show = [&](vector<Point> pts, const char* note) {
        cout << note << ": ";
        vector<Point> h = hull(pts);
        for (size_t i = 0; i < h.size(); i++) cout << (i ? " " : "") << "(" << h[i].x << "," << h[i].y << ")";
        cout << "\n";
    };
    show({{0, 0}, {4, 0}, {4, 4}, {0, 4}, {2, 2}, {2, 0}}, "square with a point inside and one in the middle of the bottom edge");
    show({{0, 0}, {1, 1}, {2, 2}, {3, 3}}, "four points on one line");
    show({{1, 1}, {1, 1}, {2, 3}}, "a repeated point and one more");
    show({{0, 0}, {6, 0}, {0, 6}, {1, 1}, {3, 3}}, "triangle, a point inside, a point in the middle of the long side");

    mt19937 rng(11);
    for (int round = 0; round < 6000; round++) {
        int n = rng() % 9 + 1, side = rng() % 4 + 2;
        vector<Point> pts;
        for (int i = 0; i < n; i++) pts.push_back({(long long)(rng() % side), (long long)(rng() % side)});
        vector<Point> h = hull(pts);
        // brute: the corners as a set of points
        sort(pts.begin(), pts.end(), [](Point a, Point b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); });
        pts.erase(unique(pts.begin(), pts.end(), [](Point a, Point b) { return a.x == b.x && a.y == b.y; }), pts.end());
        set<pair<long long, long long>> want, got;
        for (size_t k = 0; k < pts.size(); k++)
            if (isCorner(pts, k)) want.insert({pts[k].x, pts[k].y});
        for (Point p : h) got.insert({p.x, p.y});
        if (got != want || got.size() != h.size()) return 1;
        if (h.size() >= 3) {
            for (size_t i = 0; i < h.size(); i++)  // strictly left turns at every corner: counterclockwise and no flat corner
                if (cross(h[i], h[(i + 1) % h.size()], h[(i + 2) % h.size()]) <= 0) return 2;
            if (make_pair(h[0].x, h[0].y) != make_pair(pts[0].x, pts[0].y)) return 3;
        }
    }
}
