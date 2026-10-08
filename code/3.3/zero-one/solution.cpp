/*
Problem: n items with weights w_i and values v_i; choose some (each at most once) with total weight at most W,
maximising the total value.
Input: n W (1 <= n <= 100, 1 <= W <= 10^5), then n lines w_i v_i (1 <= w_i <= W, 1 <= v_i <= 10^9).
Output: the largest total value.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, W;
    cin >> n >> W;
    // best[c] = largest value with total weight at most c, using the items seen so far (Theorem 3.3.1)
    vector<long long> best(W + 1, 0);  // values up to 10^11: long long
    for (int i = 0; i < n; i++) {
        int w;
        long long v;
        cin >> w >> v;
        for (int c = W; c >= w; c--)  // downwards: best[c - w] is still the row without item i
            best[c] = max(best[c], best[c - w] + v);
    }
    cout << best[W] << "\n";
}
