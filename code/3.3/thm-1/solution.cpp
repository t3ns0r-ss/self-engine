#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.1. 0/1 knapsack in one row: the capacity loop runs downwards, so best[c - w] is still the row without the item.
vector<long long> knapsackRow(const vector<pair<int, long long>>& items, int W) {
    vector<long long> best(W + 1, 0);
    for (auto [w, v] : items)
        for (int c = W; c >= w; c--) best[c] = max(best[c], best[c - w] + v);
    return best;
}
// snippet:end

long long brute(const vector<pair<int, long long>>& items, int W) {
    long long best = 0;
    for (int mask = 0; mask < (1 << items.size()); mask++) {
        int w = 0;
        long long v = 0;
        for (size_t i = 0; i < items.size(); i++) if (mask >> i & 1) w += items[i].first, v += items[i].second;
        if (w <= W) best = max(best, v);
    }
    return best;
}
int main() {
    vector<pair<int, long long>> items = {{3, 30}, {4, 50}, {5, 60}};
    auto row = knapsackRow(items, 8);
    cout << "best value for the capacities 0..8:";
    for (long long x : row) cout << ' ' << x;
    cout << '\n';
    mt19937 rng(21);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 8, W = rng() % 20;
        vector<pair<int, long long>> it(n);
        for (auto& [w, v] : it) w = 1 + rng() % 8, v = 1 + rng() % 30;
        if (knapsackRow(it, W)[W] != brute(it, W)) return 1;
    }
}
