#include <bits/stdc++.h>
using namespace std;

/*
Problem: n rectangles with integer corners, each with a weight; a point lies in a rectangle when x1 <= x <= x2 and y1 <= y <= y2.
Find the largest total weight of the rectangles that contain one integer point, and the point with that weight that has the smallest x, then the smallest y.
Input: n, then n lines x1 y1 x2 y2 w with x1 <= x2, y1 <= y2 and 1 <= w.
Output: three numbers: the weight, x and y.
*/

// snippet:begin
// A range-add, maximum tree (Theorem 5.4.3) driven by a sweep along x (Theorem 5.4.1).
struct MaxTree {
    int m;
    vector<long long> best, here;  // best: maximum over the node of what was added at or below it; here: added to the whole node
    MaxTree(int m) : m(m), best(4 * m), here(4 * m) {}
    void add(int v, int lo, int hi, int l, int r, long long d) {  // positions l .. r-1 get d more
        if (r <= lo || hi <= l) return;
        if (l <= lo && hi <= r) { here[v] += d, best[v] += d; return; }
        int mid = (lo + hi) / 2;
        add(2 * v, lo, mid, l, r, d), add(2 * v + 1, mid, hi, l, r, d);
        best[v] = here[v] + max(best[2 * v], best[2 * v + 1]);
    }
    int leftmostMaximum() const {
        int v = 1, lo = 0, hi = m;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (best[2 * v] == best[v] - here[v]) v = 2 * v, hi = mid;
            else v = 2 * v + 1, lo = mid;
        }
        return lo;
    }
};

struct Spot { long long weight, x, y; };

// Rectangles {x1, y1, x2, y2, w}. A closed range [y1, y2] of integers is the half-open range [y1, y2 + 1), so each leaf is a
// gap that starts at one y value; the column x2 + 1 is where the rectangle stops.
Spot heaviestSpot(const vector<array<long long, 5>>& rects) {
    vector<long long> ys;
    for (auto& r : rects) ys.push_back(r[1]), ys.push_back(r[3] + 1);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int gaps = ys.size() - 1;
    MaxTree tree(gaps);
    vector<array<long long, 4>> events;  // {x, first gap, end gap, +w or -w}
    for (auto& r : rects) {
        long long lo = lower_bound(ys.begin(), ys.end(), r[1]) - ys.begin();
        long long hi = lower_bound(ys.begin(), ys.end(), r[3] + 1) - ys.begin();
        events.push_back({r[0], lo, hi, +r[4]});
        events.push_back({r[2] + 1, lo, hi, -r[4]});
    }
    sort(events.begin(), events.end());
    Spot best = {0, 0, 0};
    for (size_t i = 0; i < events.size(); i++) {
        tree.add(1, 0, gaps, events[i][1], events[i][2], events[i][3]);
        if (i + 1 < events.size() && events[i + 1][0] == events[i][0]) continue;  // read the maximum after all events at this x
        if (tree.best[1] > best.weight) best = {tree.best[1], events[i][0], ys[tree.leftmostMaximum()]};  // strictly: the smaller x wins ties
    }
    return best;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<array<long long, 5>> rects(n);
    for (auto& r : rects) cin >> r[0] >> r[1] >> r[2] >> r[3] >> r[4];
    Spot s = heaviestSpot(rects);
    cout << s.weight << " " << s.x << " " << s.y << "\n";
}
