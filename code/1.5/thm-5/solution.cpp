#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.5. The fewest segments (l, r) that cover [0, L], or -1: among the segments starting inside the covered part,
// take the one reaching farthest.
int coverSegment(vector<pair<int, int>> seg, int L) {
    sort(seg.begin(), seg.end());
    int reach = 0, used = 0, i = 0, n = seg.size();
    while (reach < L) {
        int best = reach;
        while (i < n && seg[i].first <= reach) best = max(best, seg[i++].second);
        if (best == reach) return -1;  // nothing extends the cover: a gap
        reach = best;
        used++;
    }
    return used;
}
// snippet:end

int main() {
    cout << "[0,3] [2,5] [4,8], cover [0,8]: " << coverSegment({{0, 3}, {2, 5}, {4, 8}}, 8) << " segments\n";
    cout << "[0,5] [3,8] [1,2], cover [0,8]: " << coverSegment({{0, 5}, {3, 8}, {1, 2}}, 8) << " segments\n";
    cout << "[0,2] [3,5], cover [0,5]: " << (coverSegment({{0, 2}, {3, 5}}, 5) < 0 ? "impossible" : "possible") << '\n';
    mt19937 rng(5);
    for (int round = 0; round < 400; round++) {
        int n = rng() % 6 + 1, L = rng() % 8 + 1;
        vector<pair<int, int>> v(n);
        for (auto& p : v) p.first = rng() % L, p.second = p.first + rng() % 5 + 1;
        int best = -1;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<pair<int, int>> u;
            for (int i = 0; i < n; i++) if (mask >> i & 1) u.push_back(v[i]);
            sort(u.begin(), u.end());
            int reach = 0;
            for (auto [l, r] : u) if (l <= reach) reach = max(reach, r);
            if (reach >= L && (best < 0 || __builtin_popcount(mask) < best)) best = __builtin_popcount(mask);
        }
        if (best != coverSegment(v, L)) return 1;
    }
}
