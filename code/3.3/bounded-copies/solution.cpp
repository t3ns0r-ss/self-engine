/*
Problem: n kinds of items; kind i has weight w_i, value v_i and c_i copies. Choose copies with total weight at
most W, maximising the total value.
Input: n W (1 <= n <= 100, 1 <= W <= 10^5), then n lines w_i v_i c_i (1 <= w_i <= W, 1 <= v_i <= 10^6,
1 <= c_i <= 1000).
Output: the largest total value.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, W;
    cin >> n >> W;
    vector<long long> best(W + 1, 0);  // values up to 10^11
    for (int i = 0; i < n; i++) {
        long long w, v;
        int c;
        cin >> w >> v >> c;
        // bundles of 1, 2, 4, ... copies, then the remainder (Theorem 3.3.5); each bundle is a 0/1 item
        for (int size = 1; c > 0; size *= 2) {
            int take = min(size, c);
            c -= take;
            long long bw = w * take, bv = v * take;
            for (long long cap = W; cap >= bw; cap--) best[cap] = max(best[cap], best[cap - bw] + bv);
        }
    }
    cout << best[W] << "\n";
}
