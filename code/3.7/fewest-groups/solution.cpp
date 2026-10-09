/*
Problem: n items with weights w_i must be split into groups of total weight at most C each.
Print the fewest groups.
Input: n C (1 <= n <= 20, 1 <= C <= 10^9), then w_1..w_n (1 <= w_i <= C).
Output: the fewest groups.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long cap;
    cin >> n >> cap;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    // best[mask] = smallest (groups used, weight in the last group) for the items of mask (Theorem 3.7.3)
    vector<pair<int, long long>> best(1 << n, {INT_MAX, 0});
    best[0] = {1, 0};                              // one empty group open
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int j = 0; j < n; j++) {
            if (!(mask >> j & 1)) continue;
            auto [groups, fill] = best[mask ^ 1 << j];   // pack the others first, then item j last
            pair<int, long long> option = (fill + w[j] <= cap) ? make_pair(groups, fill + w[j])
                                                              : make_pair(groups + 1, w[j]);
            best[mask] = min(best[mask], option);
        }
    }
    cout << best[(1 << n) - 1].first << "\n";
}
