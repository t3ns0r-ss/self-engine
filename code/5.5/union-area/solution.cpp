#include <bits/stdc++.h>
using namespace std;

/*
Problem: area of the union of n axis-parallel rectangles.
Input: n, then n lines x1 y1 x2 y2 with x1 < x2 and y1 < y2 (the rectangle [x1, x2) x [y1, y2)).
Output: the area of the union.
*/

// snippet:begin
// A counted-cover tree over the y gaps (Theorem 5.5.2) and the sweep along x (Theorem 5.5.1).
struct CoverTree {
    int m;
    vector<int> count;                // intervals placed exactly at the node
    vector<long long> whole, inside;  // whole length of the node; covered length by intervals at or below it
    CoverTree(const vector<long long>& width) : m(width.size()), count(4 * m), whole(4 * m), inside(4 * m) { build(1, 0, m, width); }
    void build(int v, int lo, int hi, const vector<long long>& width) {
        if (hi - lo == 1) { whole[v] = width[lo]; return; }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, width), build(2 * v + 1, mid, hi, width);
        whole[v] = whole[2 * v] + whole[2 * v + 1];
    }
    void add(int v, int lo, int hi, int l, int r, int d) {  // gaps l .. r-1 get d more intervals
        if (r <= lo || hi <= l) return;
        if (l <= lo && hi <= r) count[v] += d;
        else add(2 * v, lo, (lo + hi) / 2, l, r, d), add(2 * v + 1, (lo + hi) / 2, hi, l, r, d);
        inside[v] = count[v] > 0 ? whole[v] : (hi - lo == 1 ? 0 : inside[2 * v] + inside[2 * v + 1]);
    }
};

long long unionArea(const vector<array<long long, 4>>& rects) {
    vector<long long> ys;
    for (auto& r : rects) ys.push_back(r[1]), ys.push_back(r[3]);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int gaps = ys.size() - 1;  // a leaf is the gap between two neighbouring y values, not a point
    vector<long long> width(gaps);
    for (int g = 0; g < gaps; g++) width[g] = ys[g + 1] - ys[g];
    CoverTree tree(width);
    vector<array<long long, 4>> events;  // {x, first gap, end gap, +1 or -1}
    for (auto& r : rects) {
        long long lo = lower_bound(ys.begin(), ys.end(), r[1]) - ys.begin();
        long long hi = lower_bound(ys.begin(), ys.end(), r[3]) - ys.begin();
        events.push_back({r[0], lo, hi, +1});
        events.push_back({r[2], lo, hi, -1});
    }
    sort(events.begin(), events.end());
    long long area = 0;  // long long: the area can reach 10^18
    for (size_t i = 0; i < events.size(); i++) {
        tree.add(1, 0, gaps, events[i][1], events[i][2], events[i][3]);
        if (i + 1 < events.size() && events[i + 1][0] != events[i][0])  // all events at this x are done
            area += tree.inside[1] * (events[i + 1][0] - events[i][0]);
    }
    return area;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<array<long long, 4>> rects(n);
    for (auto& r : rects) cin >> r[0] >> r[1] >> r[2] >> r[3];
    cout << unionArea(rects) << "\n";
}
