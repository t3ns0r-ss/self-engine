/*
Problem: AtCoder ABC 383 D, 9 Divisors.
Input: N (1 <= N <= 4*10^12).
Output: the number of integers in [1, N] with exactly 9 positive divisors.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The numbers up to N with exactly 9 divisors are p^8 or p^2 q^2 (p < q primes); sieve the primes up to sqrt(N).
long long nineDivisors(long long N) {
    long long s = sqrtl((long double)N);  // exact integer square root (topic 0.1)
    while (s * s > N) s--;
    while ((s + 1) * (s + 1) <= N) s++;
    int S = max(2LL, s);
    vector<char> composite(S + 1, 0);
    vector<int> cnt(S + 1, 0);  // cnt[x] = number of primes <= x
    for (int p = 2; (long long)p * p <= S; p++)
        if (!composite[p])
            for (int j = p * p; j <= S; j += p) composite[j] = 1;
    for (int x = 2; x <= S; x++) cnt[x] = cnt[x - 1] + (composite[x] ? 0 : 1);
    long long ans = 0;
    for (int p = 2; p <= S; p++) {
        if (composite[p]) continue;
        long long p8 = 1;  // p^8 <= N: one prime with exponent 8
        for (int k = 0; k < 8 && p8 <= N; k++) p8 *= p;
        if (p8 <= N) ans++;
        long long qmax = s / p;  // p^2 q^2 <= N  <=>  p q <= s, with q > p prime
        if (qmax > p) ans += cnt[qmax] - cnt[p];
    }
    return ans;
}
// snippet:end

int main() {
    long long N;
    cin >> N;
    cout << nineDivisors(N) << "\n";
}
