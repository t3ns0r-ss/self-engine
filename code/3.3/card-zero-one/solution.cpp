#include <bits/stdc++.h>
using namespace std;

long long knapsack(const vector<pair<long long, long long>>& items, int W) {
    vector<long long> best(W + 1, 0);
    for (auto [w, v] : items) for (int c = W; c >= w; c--) best[c] = max(best[c], best[c - w] + v);
    return best[W];
}
long long bruteSubsets(const vector<pair<long long, long long>>& items, long long W) {
    long long best = 0;
    for (int mask = 0; mask < (1 << items.size()); mask++) {
        long long w = 0, v = 0;
        for (size_t i = 0; i < items.size(); i++) if (mask >> i & 1) w += items[i].first, v += items[i].second;
        if (w <= W) best = max(best, v);
    }
    return best;
}
int main() {
    // P1: the items (3, 30), (4, 50), (5, 60) with capacity 8, each at most once. Brute: all 8 subsets. Method: the table.
    vector<pair<long long, long long>> items = {{3, 30}, {4, 50}, {5, 60}};
    cout << "P1 brute=" << bruteSubsets(items, 8) << " method=" << knapsack(items, 8) << '\n';
    // N1: the same items when they can be split into fractions; the table gives the whole-item answer 90.
    // Brute: take by value per weight (12.5, 12, 10): all of (4, 50), then 4 of the 5 units of (5, 60).
    long long fractional = 50 + 60 * 4 / 5;
    cout << "N1 brute=" << fractional << " method=" << knapsack(items, 8) << '\n';
    // N2: three items with weights and values up to 10^9 and capacity 10^9; the table has 3 * 10^9 cells.
    vector<pair<long long, long long>> big = {{600000000, 700000000}, {500000000, 600000000}, {400000000, 450000000}};
    long long cells = 3LL * 1000000001LL;
    cout << "N2 brute=" << bruteSubsets(big, 1000000000) << " method=" << (cells > 100000000LL ? "too-slow" : "ok") << '\n';
}
