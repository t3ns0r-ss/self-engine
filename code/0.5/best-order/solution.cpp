/*
Problem: visit all n places once, in any order, starting anywhere; moving from i to j costs w[i][j].
Find the smallest total cost.
Input: n (1 <= n <= 9), then the n x n matrix w (0 <= w[i][j] <= 10^9; w need not be symmetric).
Output: the smallest total cost.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> w(n, vector<long long>(n));
    for (auto& row : w)
        for (auto& x : row) cin >> x;
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);  // 0, 1, ..., n-1: the smallest order
    long long best = LLONG_MAX;
    do {
        long long cost = 0;
        for (int i = 0; i + 1 < n; i++) cost += w[order[i]][order[i + 1]];
        best = min(best, cost);
    } while (next_permutation(order.begin(), order.end()));  // every order once (Theorem 0.5.3)
    cout << best << "\n";
}
