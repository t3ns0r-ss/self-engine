/*
Problem: CSES 1093, Two Sets II. Count the ways to divide 1, 2, ..., n into two sets with equal sums (a division
and the same division with the two sets swapped count once), modulo 10^9 + 7.
Input: n (1 <= n <= 500).
Output: the number of divisions modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// CSES 1093. The divisions of 1..n into two sets with equal sums: ways[s] = the subsets with sum exactly s (downwards, each
// number once); each division is counted twice, so multiply by the inverse of 2.
long long twoSets(int n) {
    const long long MOD = 1000000007;
    int total = n * (n + 1) / 2;
    if (total % 2 != 0) return 0;  // odd total: no equal split
    int half = total / 2;
    vector<long long> ways(half + 1, 0);
    ways[0] = 1;
    for (int k = 1; k <= n; k++)
        for (int s = half; s >= k; s--) ways[s] = (ways[s] + ways[s - k]) % MOD;
    return ways[half] * ((MOD + 1) / 2) % MOD;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    cout << twoSets(n) << "\n";
}
