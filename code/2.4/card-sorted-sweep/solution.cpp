#include <bits/stdc++.h>
using namespace std;

// Card unit for "Hull or nearest pair in one sorted pass". Each line prints the brute-force answer and the answer of the card's method
// for one inline example, in the order of the examples in the topic file.

struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }

vector<Point> hull(vector<Point> pts) {  // Theorem 2.4.5
    sort(pts.begin(), pts.end(), [](Point a, Point b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); });
    pts.erase(unique(pts.begin(), pts.end(), [](Point a, Point b) { return a.x == b.x && a.y == b.y; }), pts.end());
    if (pts.size() < 2) return pts;
    vector<Point> h;
    for (int pass = 0; pass < 2; pass++) {
        size_t start = h.size();
        for (Point p : pts) {
            while (h.size() >= start + 2 && cross(h[h.size() - 2], h.back(), p) <= 0) h.pop_back();
            h.push_back(p);
        }
        h.pop_back();
        reverse(pts.begin(), pts.end());
    }
    return h;
}

long long closestPairSquared(vector<Point> p) {  // Theorem 2.4.6
    sort(p.begin(), p.end(), [](Point a, Point b) { return a.x < b.x; });
    set<pair<long long, long long>> window;
    long long best = LLONG_MAX;
    size_t behind = 0;
    for (size_t i = 0; i < p.size(); i++) {
        long long r = (long long)sqrtl((long double)best) + 1;
        while (p[i].x - p[behind].x >= r) window.erase({p[behind].y, p[behind].x}), behind++;
        for (auto it = window.lower_bound({p[i].y - r, LLONG_MIN}); it != window.end() && it->first <= p[i].y + r; ++it)
            best = min(best, (it->second - p[i].x) * (it->second - p[i].x) + (it->first - p[i].y) * (it->first - p[i].y));
        window.insert({p[i].y, p[i].x});
    }
    return best;
}

int main() {
    // P1: how many corners does the hull of (0,0) (4,0) (4,4) (0,4) (2,2) (2,0) have? Brute force by the picture: the points inside the
    // square and the points in the middle of a side are not corners; everything else is.
    vector<Point> pts = {{0, 0}, {4, 0}, {4, 4}, {0, 4}, {2, 2}, {2, 0}};
    int corners = 0;
    for (size_t k = 0; k < pts.size(); k++) {
        bool inSquare = 0 < pts[k].x && pts[k].x < 4 && 0 < pts[k].y && pts[k].y < 4;  // inside the square
        bool onEdgeMiddle = (pts[k].y == 0 && 0 < pts[k].x && pts[k].x < 4) || (pts[k].y == 4 && 0 < pts[k].x && pts[k].x < 4) ||
                            (pts[k].x == 0 && 0 < pts[k].y && pts[k].y < 4) || (pts[k].x == 4 && 0 < pts[k].y && pts[k].y < 4);
        if (!inSquare && !onEdgeMiddle) corners++;
    }
    cout << "P1 brute=" << corners << " method=" << hull(pts).size() << "\n";
    // P2: the smallest squared distance among (0,0) (3,4) (1,1) (5,5). Brute force: all pairs.
    vector<Point> q = {{0, 0}, {3, 4}, {1, 1}, {5, 5}};
    long long all = LLONG_MAX;
    for (size_t i = 0; i < q.size(); i++)
        for (size_t j = i + 1; j < q.size(); j++) all = min(all, (q[i].x - q[j].x) * (q[i].x - q[j].x) + (q[i].y - q[j].y) * (q[i].y - q[j].y));
    cout << "P2 brute=" << all << " method=" << closestPairSquared(q) << "\n";
    // N1: the largest Manhattan distance |dx| + |dy| among (0,0) (10,0) (6,6). Brute force: all pairs. The hull method takes the pair
    // that is farthest in the ordinary (Euclidean) distance among the hull corners and reports its Manhattan distance.
    vector<Point> m = {{0, 0}, {10, 0}, {6, 6}};
    long long manhattan = 0;
    for (size_t i = 0; i < m.size(); i++)
        for (size_t j = i + 1; j < m.size(); j++) manhattan = max(manhattan, llabs(m[i].x - m[j].x) + llabs(m[i].y - m[j].y));
    vector<Point> h = hull(m);
    long long farthest = -1, reported = 0;
    for (size_t i = 0; i < h.size(); i++)
        for (size_t j = i + 1; j < h.size(); j++) {
            long long e = (h[i].x - h[j].x) * (h[i].x - h[j].x) + (h[i].y - h[j].y) * (h[i].y - h[j].y);
            if (e > farthest) farthest = e, reported = llabs(h[i].x - h[j].x) + llabs(h[i].y - h[j].y);
        }
    cout << "N1 brute=" << manhattan << " method=" << reported << "\n";
}
