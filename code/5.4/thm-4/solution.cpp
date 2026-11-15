#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.4.4. For every rectangle {a, b, c, d} (the points with a <= x <= b and c <= y <= d), count the points inside.
// Offline: G(X, Y) = number of points with x <= X and y <= Y is read from a Fenwick tree while X increases.
vector<int> countInRectangles(vector<pair<int, int>> points, const vector<array<int, 4>>& rects) {
    vector<int> ys;
    for (auto& p : points) ys.push_back(p.second);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<int> tree(ys.size() + 1, 0);  // Fenwick tree over the ranks of the y values
    auto rank = [&](int y) { return int(upper_bound(ys.begin(), ys.end(), y) - ys.begin()); };  // distinct y values <= y
    vector<array<int, 4>> queries;  // {X, Y, sign, rectangle}: G(X, Y) is added to or subtracted from that rectangle
    for (int i = 0; i < (int)rects.size(); i++) {
        auto [a, b, c, d] = rects[i];
        queries.insert(queries.end(), {{b, d, +1, i}, {a - 1, d, -1, i}, {b, c - 1, -1, i}, {a - 1, c - 1, +1, i}});
    }
    sort(points.begin(), points.end());
    sort(queries.begin(), queries.end());
    vector<int> answer(rects.size(), 0);
    size_t next = 0;
    for (auto& [X, Y, sign, i] : queries) {
        for (; next < points.size() && points[next].first <= X; next++)  // x <= X: points with x == X come first
            for (int k = rank(points[next].second); k < (int)tree.size(); k += k & -k) tree[k]++;
        int sum = 0;
        for (int k = rank(Y); k > 0; k -= k & -k) sum += tree[k];
        answer[i] += sign * sum;
    }
    return answer;
}
// snippet:end

vector<int> byLoops(const vector<pair<int, int>>& points, const vector<array<int, 4>>& rects) {
    vector<int> answer;
    for (auto& [a, b, c, d] : rects) {
        int count = 0;
        for (auto& [x, y] : points) count += (a <= x && x <= b && c <= y && y <= d);
        answer.push_back(count);
    }
    return answer;
}

int main() {
    vector<pair<int, int>> pts = {{1, 1}, {2, 3}, {3, 2}, {3, 3}};
    vector<array<int, 4>> rects = {{1, 3, 2, 3}, {3, 3, 3, 3}, {4, 5, 0, 5}, {1, 3, 1, 3}};
    auto got = countInRectangles(pts, rects);
    cout << "points (1,1) (2,3) (3,2) (3,3)\n";
    cout << "rectangle x 1..3, y 2..3: " << got[0] << "\n";
    cout << "rectangle x 3..3, y 3..3: " << got[1] << "\n";
    cout << "rectangle x 4..5, y 0..5: " << got[2] << "\n";
    cout << "rectangle x 1..3, y 1..3: " << got[3] << "\n";
    // Check against loops on every set of 4 points in a 3 x 3 grid (repeats allowed) with every rectangle in 1..3.
    vector<array<int, 4>> all;
    for (int a = 1; a <= 3; a++)
        for (int b = a; b <= 3; b++)
            for (int c = 1; c <= 3; c++)
                for (int d = c; d <= 3; d++) all.push_back({a, b, c, d});
    for (int mask = 0; mask < 9 * 9 * 9 * 9; mask++) {
        vector<pair<int, int>> p;
        for (int t = 0, m = mask; t < 4; t++, m /= 9) p.push_back({m % 9 / 3 + 1, m % 3 + 1});
        if (countInRectangles(p, all) != byLoops(p, all)) return 1;
    }
}
