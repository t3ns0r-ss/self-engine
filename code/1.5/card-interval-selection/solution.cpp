#include <bits/stdc++.h>
using namespace std;

int select(vector<pair<int, int>> iv, bool touchingOk) {
    sort(iv.begin(), iv.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second; });
    int chosen = 0, last = -100;
    for (auto [s, e] : iv) if (touchingOk ? s >= last : s > last) chosen++, last = e;
    return chosen;
}

int main() {
    vector<pair<int, int>> iv = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}};
    int n = iv.size();
    // P1: the most pairwise disjoint intervals (touching overlaps). Brute: every subset. Method: earliest end first.
    int brute = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++)
            if ((mask >> i & 1) && (mask >> j & 1) && max(iv[i].first, iv[j].first) <= min(iv[i].second, iv[j].second)) ok = false;
        if (ok) brute = max(brute, __builtin_popcount(mask));
    }
    cout << "P1 brute=" << brute << " method=" << select(iv, false) << '\n';
    // P2: the fewest points that hit every interval. Brute: every set of points among 0..11. Method: the chosen ends.
    int bestPoints = INT_MAX;
    for (int mask = 0; mask < (1 << 12); mask++) {
        bool all = true;
        for (auto [s, e] : iv) { bool hit = false; for (int x = s; x <= e; x++) hit |= mask >> x & 1; all &= hit; }
        if (all) bestPoints = min(bestPoints, __builtin_popcount(mask));
    }
    cout << "P2 brute=" << bestPoints << " method=" << select(iv, false) << '\n';
    // N1: [1,5] [2,3] [4,6] [7,8] cannot all be kept; how many groups of disjoint intervals are needed? Brute: the
    // largest overlap at one point. Method: the number of disjoint intervals chosen.
    vector<pair<int, int>> g = {{1, 5}, {2, 3}, {4, 6}, {7, 8}};
    int overlap = 0;
    for (int x = 0; x <= 8; x++) { int c = 0; for (auto [s, e] : g) c += s <= x && x <= e; overlap = max(overlap, c); }
    cout << "N1 brute=" << overlap << " method=" << select(g, false) << '\n';
    // N2: [1,3] and [3,5] touch at 3, which counts as overlapping; the greedy test is s >= lastEnd instead of s > lastEnd.
    vector<pair<int, int>> t = {{1, 3}, {3, 5}};
    cout << "N2 brute=" << select(t, false) << " method=" << select(t, true) << '\n';
}
