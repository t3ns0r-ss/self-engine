/*
Problem: LeetCode 2741 Special Permutations, as a program. Given n distinct positive integers, count the orders in
which every two neighbours divide one another (one of them is a multiple of the other), modulo 10^9 + 7.
Input: n (2 <= n <= 14), then the n numbers (1 <= value <= 10^9).
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    auto fits = [&](int i, int j) { return a[i] % a[j] == 0 || a[j] % a[i] == 0; };
    // ways[mask][v] = orders of exactly the numbers in mask that end with number v (Theorem 3.7.2, counting)
    vector<vector<long long>> ways(1 << n, vector<long long>(n, 0));
    for (int v = 0; v < n; v++) ways[1 << v][v] = 1;   // any number may start
    for (int mask = 1; mask < (1 << n); mask++)
        for (int v = 0; v < n; v++) {
            if (ways[mask][v] == 0) continue;
            for (int u = 0; u < n; u++)
                if (!(mask >> u & 1) && fits(v, u))
                    ways[mask | 1 << u][u] = (ways[mask | 1 << u][u] + ways[mask][v]) % MOD;
        }
    long long total = 0;
    for (int v = 0; v < n; v++) total = (total + ways[(1 << n) - 1][v]) % MOD;
    cout << total << "\n";
}
