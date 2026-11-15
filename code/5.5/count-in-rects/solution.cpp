#include <bits/stdc++.h>
using namespace std;

/*
Problem: n points and q rectangles (closed, sides parallel to the axes). For every rectangle, count the points inside it.
Input: n and q, then n lines x y, then q lines a b c d (the rectangle a <= x <= b, c <= y <= d, with a <= b and c <= d).
Output: q lines, the count for each rectangle.
*/

// snippet:begin
// Offline counting with a Fenwick tree over y while the sweep moves along x (Theorem 5.5.4).
// G(X, Y) = points with x <= X and y <= Y; a rectangle is G(b, d) - G(a - 1, d) - G(b, c - 1) + G(a - 1, c - 1).
vector<int> countInRectangles(vector<pair<int, int>> points, const vector<array<int, 4>>& rects) {
    vector<int> ys;
    for (auto& p : points) ys.push_back(p.second);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<int> tree(ys.size() + 1, 0);  // Fenwick tree over the ranks of the y values
    auto rank = [&](int y) { return int(upper_bound(ys.begin(), ys.end(), y) - ys.begin()); };  // distinct y values <= y
    vector<array<int, 4>> queries;  // {X, Y, sign, rectangle}
    for (int i = 0; i < (int)rects.size(); i++) {
        auto [a, b, c, d] = rects[i];
        queries.insert(queries.end(), {{b, d, +1, i}, {a - 1, d, -1, i}, {b, c - 1, -1, i}, {a - 1, c - 1, +1, i}});
    }
    sort(points.begin(), points.end());
    sort(queries.begin(), queries.end());
    vector<int> answer(rects.size(), 0);
    size_t next = 0;
    for (auto& [X, Y, sign, i] : queries) {
        for (; next < points.size() && points[next].first <= X; next++)  // x <= X: points with x == X are added first
            for (int k = rank(points[next].second); k < (int)tree.size(); k += k & -k) tree[k]++;
        int sum = 0;
        for (int k = rank(Y); k > 0; k -= k & -k) sum += tree[k];
        answer[i] += sign * sum;
    }
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> points(n);
    for (auto& p : points) cin >> p.first >> p.second;
    vector<array<int, 4>> rects(q);
    for (auto& r : rects) cin >> r[0] >> r[1] >> r[2] >> r[3];
    for (int count : countInRectangles(points, rects)) cout << count << "\n";
}
