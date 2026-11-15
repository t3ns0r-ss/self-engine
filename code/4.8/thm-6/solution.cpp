#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.8.6. The smallest squared distance between two of n >= 2 different points.
struct Point { long long x, y; };
long long closestPairSquared(vector<Point> p) {
    sort(p.begin(), p.end(), [](Point a, Point b) { return a.x < b.x; });
    set<pair<long long, long long>> window;  // (y, x) of the points whose x is less than r behind the current one
    long long best = LLONG_MAX;              // smallest squared distance so far
    size_t behind = 0;                       // p[behind] is the oldest point still in the window
    for (size_t i = 0; i < p.size(); i++) {
        long long r = (long long)sqrtl((long double)best) + 1;  // r is more than the best distance, so nothing useful is lost
        while (p[i].x - p[behind].x >= r) window.erase({p[behind].y, p[behind].x}), behind++;
        for (auto it = window.lower_bound({p[i].y - r, LLONG_MIN}); it != window.end() && it->first <= p[i].y + r; ++it) {
            long long dx = it->second - p[i].x, dy = it->first - p[i].y;
            best = min(best, dx * dx + dy * dy);
        }
        window.insert({p[i].y, p[i].x});
    }
    return best;
}
// snippet:end

int main() {
    auto show = [&](vector<Point> p, const char* note) {
        cout << note << ": " << closestPairSquared(p) << "\n";
    };
    show({{0, 0}, {3, 4}, {1, 1}, {5, 5}}, "(0,0) (3,4) (1,1) (5,5)");
    show({{0, 0}, {10, 0}, {5, 0}}, "(0,0) (10,0) (5,0)");
    show({{2, 0}, {2, 3}, {2, 7}}, "(2,0) (2,3) (2,7), all in one column");
    show({{-1000000000, -1000000000}, {1000000000, 1000000000}}, "two corners of the biggest square");

    mt19937 rng(5);
    for (int round = 0; round < 20000; round++) {
        int n = rng() % 9 + 2, side = rng() % 8 + 3;
        set<pair<long long, long long>> used;
        vector<Point> p;
        while ((int)p.size() < n && (int)used.size() < side * side) {
            Point c = {(long long)(rng() % side), (long long)(rng() % side)};
            if (used.insert({c.x, c.y}).second) p.push_back(c);
        }
        if (p.size() < 2) continue;
        long long want = LLONG_MAX;
        for (size_t i = 0; i < p.size(); i++)
            for (size_t j = i + 1; j < p.size(); j++) want = min(want, (p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
        if (closestPairSquared(p) != want) return 1;
    }
}
