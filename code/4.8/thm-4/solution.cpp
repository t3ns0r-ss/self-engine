#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.8.4. Where is q relative to a simple polygon p (corners in either direction)? 0 outside, 1 on the boundary, 2 inside.
struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
bool inBox(Point a, Point b, Point q) {  // q is inside the bounding box of ab
    return min(a.x, b.x) <= q.x && q.x <= max(a.x, b.x) && min(a.y, b.y) <= q.y && q.y <= max(a.y, b.y);
}
int locate(const vector<Point>& p, Point q) {
    bool inside = false;
    for (size_t i = 0; i < p.size(); i++) {
        Point a = p[i], b = p[(i + 1) % p.size()];
        long long c = cross(a, b, q);
        if (c == 0 && inBox(a, b, q)) return 1;  // the boundary first
        // The edge counts when exactly one end is above q (so an end at q's height counts as below) and it passes right of q.
        if ((a.y > q.y) != (b.y > q.y) && (c > 0) == (b.y > a.y)) inside = !inside;
    }
    return inside ? 2 : 0;
}
// snippet:end

// Reference by another method: exact boundary test with a dot product, then the winding number from the angles at q.
int locateByAngles(const vector<Point>& p, Point q) {
    double total = 0;
    for (size_t i = 0; i < p.size(); i++) {
        Point a = p[i], b = p[(i + 1) % p.size()];
        long long cr = (a.x - q.x) * (b.y - q.y) - (a.y - q.y) * (b.x - q.x);
        long long dot = (a.x - q.x) * (b.x - q.x) + (a.y - q.y) * (b.y - q.y);
        if (cr == 0 && dot <= 0) return 1;  // q is between a and b (or at one of them)
        total += atan2((double)cr, (double)dot);
    }
    return fabs(total) > M_PI ? 2 : 0;  // a full turn (2 pi) around q means inside
}

int main() {
    auto show = [&](const vector<Point>& p, Point q, const char* note) {
        static const char* name[] = {"outside", "on the boundary", "inside"};
        cout << "(" << q.x << "," << q.y << "): " << name[locate(p, q)] << " (" << note << ")\n";
    };
    vector<Point> square = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<Point> diamond = {{2, 0}, {4, 2}, {2, 4}, {0, 2}};
    cout << "square (0,0) (4,0) (4,4) (0,4)\n";
    show(square, {2, 2}, "the middle");
    show(square, {4, 2}, "on the right edge");
    show(square, {5, 2}, "level with the edge, but beyond it");
    cout << "diamond (2,0) (4,2) (2,4) (0,2)\n";
    show(diamond, {1, 2}, "the ray to the right passes through the corner (4,2)");
    show(diamond, {-1, 2}, "the ray passes through the corners (0,2) and (4,2)");

    // Star-shaped polygons around the centre (3,3): corners in order of angle, so the polygon is simple.
    mt19937 rng(7);
    int checked = 0;
    for (int round = 0; round < 4000; round++) {
        int n = rng() % 6 + 3;
        vector<Point> pts;
        for (int i = 0; i < n; i++) {
            Point c = {(long long)(rng() % 7), (long long)(rng() % 7)};
            if (c.x == 3 && c.y == 3) continue;
            pts.push_back(c);
        }
        sort(pts.begin(), pts.end(), [](Point a, Point b) { return atan2((double)a.y - 3, (double)a.x - 3) < atan2((double)b.y - 3, (double)b.x - 3); });
        vector<Point> poly;
        for (Point c : pts) {
            // keep one corner for each direction from the centre: skip a corner with the same direction as the last kept one
            if (!poly.empty()) {
                Point l = poly.back();
                if ((l.x - 3) * (c.y - 3) - (l.y - 3) * (c.x - 3) == 0 && (l.x - 3) * (c.x - 3) + (l.y - 3) * (c.y - 3) > 0) continue;
            }
            poly.push_back(c);
        }
        if (poly.size() >= 3) {
            Point f = poly[0], l = poly.back();
            if ((l.x - 3) * (f.y - 3) - (l.y - 3) * (f.x - 3) == 0 && (l.x - 3) * (f.x - 3) + (l.y - 3) * (f.y - 3) > 0) poly.pop_back();
        }
        if (poly.size() < 3) continue;
        bool ok = true;  // every gap between neighbouring directions must be less than half a turn, so that the centre is inside
        for (size_t i = 0; i < poly.size(); i++) {
            Point a = poly[i], b = poly[(i + 1) % poly.size()];
            if ((a.x - 3) * (b.y - 3) - (a.y - 3) * (b.x - 3) <= 0) ok = false;
        }
        if (!ok) continue;
        checked++;
        for (int x = -1; x <= 7; x++)
            for (int y = -1; y <= 7; y++)
                if (locate(poly, {x, y}) != locateByAngles(poly, {x, y})) return 1;
        reverse(poly.begin(), poly.end());  // the same polygon, clockwise
        for (int x = -1; x <= 7; x++)
            for (int y = -1; y <= 7; y++)
                if (locate(poly, {x, y}) != locateByAngles(poly, {x, y})) return 1;
    }
    if (checked < 200) return 2;  // the generator must have produced many polygons
}
