#include <bits/stdc++.h>
using namespace std;

/*
Problem: n closed horizontal or vertical segments, each of positive length. Count the pairs (horizontal, vertical) that share a point.
Input: n, then n lines x1 y1 x2 y2 with x1 <= x2 and y1 <= y2; exactly one of x1 = x2 (vertical) and y1 = y2 (horizontal) holds.
Output: the number of crossing pairs.
*/

// snippet:begin
// Sweep along x (Theorem 5.5.1) with a Fenwick tree over y that holds the horizontal segments alive at the sweep position (Theorem 5.5.4).
long long countCrossings(const vector<array<int, 4>>& segs) {
    vector<int> ys;
    for (auto& s : segs)
        if (s[1] == s[3]) ys.push_back(s[1]);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<int> tree(ys.size() + 1, 0);
    auto change = [&](int y, int d) {
        for (int i = lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1; i < (int)tree.size(); i += i & -i) tree[i] += d;
    };
    auto aliveUpTo = [&](int y) {  // live horizontal segments with height <= y
        int sum = 0;
        for (int i = upper_bound(ys.begin(), ys.end(), y) - ys.begin(); i > 0; i -= i & -i) sum += tree[i];
        return sum;
    };
    enum { OPEN = 0, ASK = 1, CLOSE = 2 };  // at one x: open first, then ask, then close, because the segments are closed
    vector<array<int, 4>> events;           // {x, kind, y or lowest y, highest y}
    for (auto& s : segs) {
        if (s[1] == s[3]) events.push_back({s[0], OPEN, s[1], 0}), events.push_back({s[2], CLOSE, s[1], 0});
        else events.push_back({s[0], ASK, s[1], s[3]});
    }
    sort(events.begin(), events.end());
    long long total = 0;  // long long: up to (n / 2)^2 pairs
    for (auto& [x, kind, a, b] : events) {
        if (kind == OPEN) change(a, +1);
        else if (kind == CLOSE) change(a, -1);
        else total += aliveUpTo(b) - aliveUpTo(a - 1);
    }
    return total;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<array<int, 4>> segs(n);
    for (auto& s : segs) cin >> s[0] >> s[1] >> s[2] >> s[3];
    cout << countCrossings(segs) << "\n";
}
