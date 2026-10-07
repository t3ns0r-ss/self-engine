/*
Problem: ABC 356 D Masked Popcount. The sum of popcount(k AND M) over k = 0 .. N, modulo 998244353.
Input: N M (0 <= N, M < 2^60).
Output: the sum modulo 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    const long long MOD = 998244353;
    long long total = 0;
    for (int b = 0; b < 60; b++) {
        if (!((m >> b) & 1)) continue;  // bit b of k & M is 0 for every k
        // among 0 .. n, bit b repeats 2^b zeros then 2^b ones, with period 2^(b+1)
        long long period = 1LL << (b + 1), half = 1LL << b;
        long long cnt = (n + 1) / period * half + max(0LL, (n + 1) % period - half);
        total = (total + cnt % MOD) % MOD;  // Theorem 1.7.3: popcount adds 1 per set bit
    }
    cout << total << "\n";
}
