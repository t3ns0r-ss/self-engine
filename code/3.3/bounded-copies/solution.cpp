/*
Problem: n kinds of items; kind i has weight w_i, value v_i and c_i copies. Choose copies with total weight at
most W, maximising the total value.
Input: n W (1 <= n <= 100, 1 <= W <= 10^5), then n lines w_i v_i c_i (1 <= w_i <= W, 1 <= v_i <= 10^6,
1 <= c_i <= 1000).
Output: the largest total value.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.5. Split the c copies of an item into bundles of 1, 2, 4, ... copies and a remainder; each bundle is a 0/1 item.
long long boundedKnapsack(const vector<array<long long, 3>>& kinds, int W) {  // {weight, value, copies}
    vector<long long> best(W + 1, 0);
    for (auto [w, v, c] : kinds)
        for (long long size = 1; c > 0; size *= 2) {
            long long take = min(size, c);
            c -= take;
            long long bw = w * take, bv = v * take;
            for (long long cap = W; cap >= bw; cap--) best[cap] = max(best[cap], best[cap - bw] + bv);
        }
    return best[W];
}
// snippet:end

int main() {
    int n, W;
    cin >> n >> W;
    vector<array<long long, 3>> kinds(n);
    for (auto& k : kinds) cin >> k[0] >> k[1] >> k[2];
    cout << boundedKnapsack(kinds, W) << "\n";
}
