/*
Problem: the values a_1..a_n are put in a uniformly random order; print the expected number of
inversions (pairs i < j with b_i > b_j in the new order) modulo 998244353.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (1 <= a_i <= 10^9).
Output: the expected value as P * Q^(-1) mod 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

int main() {
    int n;
    cin >> n;
    map<long long, long long> cnt;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        cnt[a]++;
    }
    long long pairs = (long long)n * (n - 1) / 2;  // all pairs of positions
    for (auto [v, c] : cnt) pairs -= c * (c - 1) / 2;  // pairs of equal values are never inverted
    // each pair of different values is inverted with probability 1/2 (Theorem 2.4.2)
    long long inv2 = (MOD + 1) / 2;
    cout << pairs % MOD * inv2 % MOD << "\n";
}
