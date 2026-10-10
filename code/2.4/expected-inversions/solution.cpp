/*
Problem: the values a_1..a_n are put in a uniformly random order; print the expected number of
inversions (pairs i < j with b_i > b_j in the new order) modulo 998244353.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (1 <= a_i <= 10^9).
Output: the expected value as P * Q^(-1) mod 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.4.2. The expected inversions of a random order: each pair of different values is inverted with probability
// 1/2, a pair of equal values never. Printed modulo 998244353.
long long expectedInversions(const vector<long long>& a) {
    const long long MOD = 998244353;
    long long n = a.size();
    map<long long, long long> cnt;
    for (long long x : a) cnt[x]++;
    long long pairs = n * (n - 1) / 2;
    for (auto [v, c] : cnt) pairs -= c * (c - 1) / 2;  // pairs of equal values
    return pairs % MOD * ((MOD + 1) / 2) % MOD;        // times the inverse of 2
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << expectedInversions(a) << "\n";
}
