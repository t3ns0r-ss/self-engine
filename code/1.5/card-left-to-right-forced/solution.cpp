#include <bits/stdc++.h>
using namespace std;

int cover(vector<pair<int, int>> seg, int L, int slack) {
    sort(seg.begin(), seg.end());
    int reach = 0, used = 0, i = 0, n = seg.size();
    while (reach < L) {
        int best = reach;
        while (i < n && seg[i].first <= reach + slack) best = max(best, seg[i++].second);
        if (best == reach) return -1;
        reach = best;
        used++;
    }
    return used;
}

int main() {
    // P1: the fewest of [0,5] [3,8] [1,2] covering [0,8]. Brute: every subset. Method: the farthest reach first.
    vector<pair<int, int>> s = {{0, 5}, {3, 8}, {1, 2}};
    int brute = -1;
    for (int mask = 0; mask < 8; mask++) {
        vector<pair<int, int>> u;
        for (int i = 0; i < 3; i++) if (mask >> i & 1) u.push_back(s[i]);
        sort(u.begin(), u.end());
        int reach = 0;
        for (auto [l, r] : u) if (l <= reach) reach = max(reach, r);
        if (reach >= 8 && (brute < 0 || __builtin_popcount(mask) < brute)) brute = __builtin_popcount(mask);
    }
    cout << "P1 brute=" << brute << " method=" << cover(s, 8, 0) << '\n';
    // N1: the best profit of one trade in 7 1 5 3 6 4, answered by adding every daily rise.
    vector<int> p = {7, 1, 5, 3, 6, 4};
    int one = 0, rises = 0;
    for (int i = 0; i < 6; i++) for (int j = i + 1; j < 6; j++) one = max(one, p[j] - p[i]);
    for (int i = 1; i < 6; i++) rises += max(0, p[i] - p[i - 1]);
    cout << "N1 brute=" << one << " method=" << rises << '\n';
    // N2: [0,2] and [3,5] cannot cover [0,5] (the point 2.5 is missing), but a rule that continues from reach + 1 accepts them.
    cout << "N2 brute=-1 method=" << cover({{0, 2}, {3, 5}}, 5, 1) << '\n';
}
