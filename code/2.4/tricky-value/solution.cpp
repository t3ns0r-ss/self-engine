#include <bits/stdc++.h>
using namespace std;

/*
Problem: an array a[1..n]. For two different positions i and j let g(i, j) be the sum of the entries after the smaller position up to
the larger one. Find the smallest value of (i - j)^2 + g(i, j)^2 over all pairs i != j.
Input: n, then n integers (|a[i]| up to 10^4, n up to 10^5).
Output: the smallest value.
*/

// snippet:begin
struct Point { long long x, y; };
// The smallest squared distance between n >= 2 different points, by the sweep of Theorem 2.4.6.
long long closestPairSquared(vector<Point> p) {
    sort(p.begin(), p.end(), [](Point a, Point b) { return a.x < b.x; });
    set<pair<long long, long long>> window;  // (y, x) of the points less than r to the left of the current one
    long long best = LLONG_MAX;
    size_t behind = 0;
    for (size_t i = 0; i < p.size(); i++) {
        long long r = (long long)sqrtl((long double)best) + 1;
        while (p[i].x - p[behind].x >= r) window.erase({p[behind].y, p[behind].x}), behind++;
        for (auto it = window.lower_bound({p[i].y - r, LLONG_MIN}); it != window.end() && it->first <= p[i].y + r; ++it) {
            long long dx = it->second - p[i].x, dy = it->first - p[i].y;
            best = min(best, dx * dx + dy * dy);
        }
        window.insert({p[i].y, p[i].x});
    }
    return best;
}
// g(i, j) = S[j] - S[i] for the prefix sums S, so the value is the squared distance between the points (i, S[i]) and (j, S[j]).
long long smallestValue(const vector<long long>& a) {
    vector<Point> points;
    long long prefix = 0;
    for (size_t i = 0; i < a.size(); i++) {
        prefix += a[i];
        points.push_back({(long long)i + 1, prefix});  // different positions give different points
    }
    return closestPairSquared(points);
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    cout << smallestValue(a) << "\n";
}
