/*
Problem: n stones with heights h_1..h_n; from stone i you may jump to any of i + 1, ..., i + k, paying |h_i - h_j|.
Print the smallest total cost to go from stone 1 to stone n.
Input: n k (1 <= n <= 10^5, 1 <= k <= 100), then h_1..h_n (1 <= h_i <= 10^4).
Output: the smallest total cost.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.1. best[i] = the smallest cost to reach stone i; every transition into i comes from a smaller index.
long long minCostJumps(const vector<int>& h, int k) {
    int n = h.size();
    vector<long long> best(n, LLONG_MAX);
    best[0] = 0;  // base case
    for (int i = 1; i < n; i++)
        for (int j = max(0, i - k); j < i; j++)
            best[i] = min(best[i], best[j] + abs(h[i] - h[j]));
    return best[n - 1];
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> h(n);
    for (int& x : h) cin >> x;
    cout << minCostJumps(h, k) << "\n";
}
