#include <bits/stdc++.h>
using namespace std;

long long bundled(const vector<array<long long, 3>>& kinds, int W) {
    vector<long long> best(W + 1, 0);
    for (auto [w, v, c] : kinds)
        for (long long size = 1; c > 0; size *= 2) {
            long long take = min(size, c);
            c -= take;
            for (long long cap = W; cap >= w * take; cap--) best[cap] = max(best[cap], best[cap - w * take] + v * take);
        }
    return best[W];
}
long long bruteCounts(const vector<array<long long, 3>>& kinds, int W) {
    long long best = 0;
    function<void(int, long long, long long)> go = [&](int i, long long weight, long long value) {
        if (i == (int)kinds.size()) { best = max(best, value); return; }
        for (long long k = 0; k <= kinds[i][2] && weight + k * kinds[i][0] <= W; k++) go(i + 1, weight + k * kinds[i][0], value + k * kinds[i][1]);
    };
    go(0, 0, 0);
    return best;
}
int main() {
    // P1: 5 copies of an item with weight 2 and value 3, capacity 7. P2: two kinds (3, 4, 2 copies) and (2, 3, 3 copies), capacity 8.
    vector<array<long long, 3>> one = {{2, 3, 5}};
    cout << "P1 brute=" << bruteCounts(one, 7) << " method=" << bundled(one, 7) << '\n';
    vector<array<long long, 3>> two = {{3, 4, 2}, {2, 3, 3}};
    cout << "P2 brute=" << bruteCounts(two, 8) << " method=" << bundled(two, 8) << '\n';
    // N1: the ways to take exactly 3 of 10 interchangeable copies, counted as subsets of the bundles 1, 2, 4, 3.
    vector<int> b = {1, 2, 4, 3};
    int viaBundles = 0;
    for (int mask = 0; mask < 16; mask++) {
        int s = 0;
        for (int i = 0; i < 4; i++) if (mask >> i & 1) s += b[i];
        viaBundles += s == 3;
    }
    cout << "N1 brute=" << 1 << " method=" << viaBundles << '\n';
}
