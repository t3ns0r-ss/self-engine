/*
Problem: ABC 356 D Masked Popcount. The sum of popcount(k AND M) over k = 0 .. N, modulo 998244353.
Input: N M (0 <= N, M < 2^60).
Output: the sum modulo 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The sum of popcount(k & m) for k = 0..n, modulo 998244353: bit b of m contributes the number of k in 0..n with bit b set.
long long maskedPopcount(long long n, long long m) {
    const long long MOD = 998244353;
    long long total = 0;
    for (int b = 0; b < 60; b++) {
        if (!((m >> b) & 1)) continue;  // bit b of k & m is 0 for every k
        // among 0..n, bit b repeats 2^b zeros then 2^b ones, with period 2^(b+1)
        long long period = 1LL << (b + 1), half = 1LL << b;
        long long cnt = (n + 1) / period * half + max(0LL, (n + 1) % period - half);
        total = (total + cnt % MOD) % MOD;
    }
    return total;
}
// snippet:end

int main() {
    long long n, m;
    cin >> n >> m;
    cout << maskedPopcount(n, m) << "\n";
}
