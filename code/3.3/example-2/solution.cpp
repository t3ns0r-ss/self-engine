/*
Problem: CSES 1093, Two Sets II. Count the ways to divide 1, 2, ..., n into two sets with equal sums (a division
and the same division with the two sets swapped count once), modulo 10^9 + 7.
Input: n (1 <= n <= 500).
Output: the number of divisions modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

int main() {
    int n;
    cin >> n;
    int total = n * (n + 1) / 2;
    if (total % 2 != 0) {  // odd total: no equal split
        cout << 0 << "\n";
        return 0;
    }
    int half = total / 2;
    // ways[s] = number of subsets of the numbers seen so far with sum exactly s (Theorem 3.3.4, as a count)
    vector<long long> ways(half + 1, 0);
    ways[0] = 1;
    for (int k = 1; k <= n; k++)
        for (int s = half; s >= k; s--)  // downwards: each number used at most once
            ways[s] = (ways[s] + ways[s - k]) % MOD;
    // each division is counted twice (once from each of its two sets): multiply by the inverse of 2 (topic 2.2)
    long long inv2 = (MOD + 1) / 2;
    cout << ways[half] * inv2 % MOD << "\n";
}
