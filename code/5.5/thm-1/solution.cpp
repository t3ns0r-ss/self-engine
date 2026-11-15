#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.5.1. Area of the union of rectangles [x1, x2) x [y1, y2), given as {x1, y1, x2, y2}.
// Sweep along x; between two neighbouring event x-values the covered y-length is constant.
long long unionArea(const vector<array<int, 4>>& rects) {
    vector<int> ys;
    for (auto& r : rects) ys.push_back(r[1]), ys.push_back(r[3]);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<int> cover(ys.size() - 1, 0);  // cover[g] = rectangles covering the y gap [ys[g], ys[g+1])
    vector<array<int, 4>> events;         // {x, gap from, gap to, +1 or -1}
    for (auto& r : rects) {
        int lo = lower_bound(ys.begin(), ys.end(), r[1]) - ys.begin();
        int hi = lower_bound(ys.begin(), ys.end(), r[3]) - ys.begin();
        events.push_back({r[0], lo, hi, +1});
        events.push_back({r[2], lo, hi, -1});
    }
    sort(events.begin(), events.end());
    long long area = 0;  // long long: the area can pass 2 * 10^9
    for (size_t i = 0; i < events.size(); i++) {
        for (int g = events[i][1]; g < events[i][2]; g++) cover[g] += events[i][3];
        if (i + 1 == events.size() || events[i + 1][0] == events[i][0]) continue;  // finish all events at this x first
        long long covered = 0;
        for (size_t g = 0; g + 1 < ys.size(); g++)
            if (cover[g] > 0) covered += ys[g + 1] - ys[g];
        area += covered * (events[i + 1][0] - events[i][0]);
    }
    return area;
}
// snippet:end

// Reference: mark every unit cell of a small grid.
long long byCells(const vector<array<int, 4>>& rects) {
    set<pair<int, int>> cells;
    for (auto& r : rects)
        for (int x = r[0]; x < r[2]; x++)
            for (int y = r[1]; y < r[3]; y++) cells.insert({x, y});
    return (long long)cells.size();
}

int main() {
    cout << "squares [0,2)x[0,2) and [1,3)x[1,3): " << unionArea({{0, 0, 2, 2}, {1, 1, 3, 3}}) << "\n";
    cout << "[0,1)x[0,1) and [1,2)x[0,1), touching at x = 1: " << unionArea({{0, 0, 1, 1}, {1, 0, 2, 1}}) << "\n";
    cout << "[0,2)x[0,3) given twice: " << unionArea({{0, 0, 2, 3}, {0, 0, 2, 3}}) << "\n";
    // Check against the cell count for every set of three rectangles with corners in 0..3.
    vector<array<int, 4>> all;
    for (int x1 = 0; x1 < 4; x1++)
        for (int x2 = x1 + 1; x2 < 4; x2++)
            for (int y1 = 0; y1 < 4; y1++)
                for (int y2 = y1 + 1; y2 < 4; y2++) all.push_back({x1, y1, x2, y2});
    for (auto& a : all)
        for (auto& b : all)
            for (auto& c : all) {
                vector<array<int, 4>> three = {a, b, c};
                if (unionArea(three) != byCells(three)) return 1;
            }
}
