#include <bits/stdc++.h>
using namespace std;

// Card unit for "Rectangles added and removed along a line" (counted cover). Each line prints the brute-force answer and the
// answer of the card's method for one inline example, in the order of the examples in the topic file.

// The method for areas: sweep along x, count rectangles per y gap (Theorem 5.5.1), half-open rectangles {x1, y1, x2, y2}.
long long unionArea(const vector<array<int, 4>>& rects) {
    vector<int> ys;
    for (auto& r : rects) ys.push_back(r[1]), ys.push_back(r[3]);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<int> cover(ys.size() - 1, 0);
    vector<array<int, 4>> events;
    for (auto& r : rects) {
        int lo = lower_bound(ys.begin(), ys.end(), r[1]) - ys.begin();
        int hi = lower_bound(ys.begin(), ys.end(), r[3]) - ys.begin();
        events.push_back({r[0], lo, hi, +1});
        events.push_back({r[2], lo, hi, -1});
    }
    sort(events.begin(), events.end());
    long long area = 0;
    for (size_t i = 0; i < events.size(); i++) {
        for (int g = events[i][1]; g < events[i][2]; g++) cover[g] += events[i][3];
        if (i + 1 == events.size() || events[i + 1][0] == events[i][0]) continue;
        long long covered = 0;
        for (size_t g = 0; g + 1 < ys.size(); g++)
            if (cover[g] > 0) covered += ys[g + 1] - ys[g];
        area += covered * (events[i + 1][0] - events[i][0]);
    }
    return area;
}

// The method for the heaviest spot: the same sweep, a weight per y gap, the largest weight over all strips (closed rectangles
// {x1, y1, x2, y2, w} become half-open by adding 1 to the upper ends).
long long heaviest(const vector<array<int, 5>>& rects) {
    vector<int> ys;
    for (auto& r : rects) ys.push_back(r[1]), ys.push_back(r[3] + 1);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<long long> weight(ys.size() - 1, 0);
    vector<array<int, 4>> events;
    for (auto& r : rects) {
        int lo = lower_bound(ys.begin(), ys.end(), r[1]) - ys.begin();
        int hi = lower_bound(ys.begin(), ys.end(), r[3] + 1) - ys.begin();
        events.push_back({r[0], lo, hi, +r[4]});
        events.push_back({r[2] + 1, lo, hi, -r[4]});
    }
    sort(events.begin(), events.end());
    long long best = 0;
    for (size_t i = 0; i < events.size(); i++) {
        for (int g = events[i][1]; g < events[i][2]; g++) weight[g] += events[i][3];
        if (i + 1 < events.size() && events[i + 1][0] == events[i][0]) continue;
        best = max(best, *max_element(weight.begin(), weight.end()));
    }
    return best;
}

// Brute force: look at every unit cell (or integer point) of the small grid.
long long cellsCoveredAtLeast(const vector<array<int, 4>>& rects, int k) {
    long long count = 0;
    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 10; y++) {
            int c = 0;
            for (auto& r : rects) c += (r[0] <= x && x < r[2] && r[1] <= y && y < r[3]);
            count += (c >= k);
        }
    return count;
}

long long heaviestByPoints(const vector<array<int, 5>>& rects) {
    long long best = 0;
    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 10; y++) {
            long long sum = 0;
            for (auto& r : rects)
                if (r[0] <= x && x <= r[2] && r[1] <= y && y <= r[3]) sum += r[4];
            best = max(best, sum);
        }
    return best;
}

int main() {
    vector<array<int, 4>> two = {{0, 0, 2, 2}, {1, 1, 3, 3}};
    // P1: area of the union of two overlapping squares.
    cout << "P1 brute=" << cellsCoveredAtLeast(two, 1) << " method=" << unionArea(two) << "\n";
    // P2: heaviest spot of three closed squares of weight 1.
    vector<array<int, 5>> three = {{0, 0, 3, 3, 1}, {2, 2, 5, 5, 1}, {3, 3, 4, 4, 1}};
    cout << "P2 brute=" << heaviestByPoints(three) << " method=" << heaviest(three) << "\n";
    // N1: the area covered by at least two squares; the cover-count sweep answers the union (at least one) instead.
    cout << "N1 brute=" << cellsCoveredAtLeast(two, 2) << " method=" << unionArea(two) << "\n";
}
