/*
Problem: n items with weights w_i and values v_i; choose some (each at most once) with total weight at most W,
maximising the total value.
Input: n W (1 <= n <= 100, 1 <= W <= 10^5), then n lines w_i v_i (1 <= w_i <= W, 1 <= v_i <= 10^9).
Output: the largest total value.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.1. best[c] = the largest value with total weight at most c; the capacity loop runs downwards, so each item is
// used at most once.
long long knapsack(const vector<pair<int, long long>>& items, int W) {  // {weight, value}
    vector<long long> best(W + 1, 0);
    for (auto [w, v] : items)
        for (int c = W; c >= w; c--) best[c] = max(best[c], best[c - w] + v);
    return best[W];
}
// snippet:end

int main() {
    int n, W;
    cin >> n >> W;
    vector<pair<int, long long>> items(n);
    for (auto& [w, v] : items) cin >> w >> v;
    cout << knapsack(items, W) << "\n";
}
