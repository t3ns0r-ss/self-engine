/*
Problem: n stones with heights h_1..h_n; from stone i you may jump to any of i + 1, ..., i + k, paying |h_i - h_j|.
Print the smallest total cost to go from stone 1 to stone n.
Input: n k (1 <= n <= 10^5, 1 <= k <= 100), then h_1..h_n (1 <= h_i <= 10^4).
Output: the smallest total cost.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> h(n);
    for (int& x : h) cin >> x;
    // best[i] = smallest cost to reach stone i (0-based); the state is the stone alone (Theorem 3.2.1)
    vector<long long> best(n, LLONG_MAX);
    best[0] = 0;  // base case
    for (int i = 1; i < n; i++)
        for (int j = max(0, i - k); j < i; j++)  // every transition into i comes from a smaller index
            best[i] = min(best[i], best[j] + abs(h[i] - h[j]));
    cout << best[n - 1] << "\n";
}
