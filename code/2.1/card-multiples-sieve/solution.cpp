#include <bits/stdc++.h>
using namespace std;

vector<bool> sieve(int N) {
    vector<bool> isPrime(N + 1, true);
    isPrime[0] = false;
    if (N >= 1) isPrime[1] = false;
    for (int p = 2; (long long)p * p <= N; p++)
        if (isPrime[p]) for (int j = p * p; j <= N; j += p) isPrime[j] = false;
    return isPrime;
}
int divisorsBrute(long long n) {
    int c = 0;
    for (long long d = 1; d <= n; d++) c += n % d == 0;
    return c;
}
vector<long long> exactPairs(const vector<int>& a, int M) {
    vector<long long> cnt(M + 1, 0), E(M + 1, 0);
    for (int v : a) cnt[v]++;
    for (int d = M; d >= 1; d--) {
        long long c = 0;
        for (int k = d; k <= M; k += d) c += cnt[k];
        E[d] = c * (c - 1) / 2;
        for (int k = 2 * d; k <= M; k += d) E[d] -= E[k];
    }
    return E;
}
int main() {
    // P1: pairs with gcd 1 in 2 4 6 3. P2: the largest gcd of a pair in 7 14 9 18. Brute: all pairs. Method: counts over multiples.
    vector<int> a = {2, 4, 6, 3};
    long long brute = 0;
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) brute += __gcd(a[i], a[j]) == 1;
    cout << "P1 brute=" << brute << " method=" << exactPairs(a, 6)[1] << '\n';
    vector<int> b = {7, 14, 9, 18};
    int bestBrute = 0, bestMethod = 0;
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) bestBrute = max(bestBrute, __gcd(b[i], b[j]));
    auto E = exactPairs(b, 18);
    for (int d = 18; d >= 1; d--) if (E[d] > 0) { bestMethod = d; break; }
    cout << "P2 brute=" << bestBrute << " method=" << bestMethod << '\n';
    // N1: pairs with gcd 1 among 600000007 and 600000011 (values up to 10^9): the array indexed by value is 4.8 GB.
    long long need = 600000011LL * 8;
    cout << "N1 brute=" << (__gcd(600000007LL, 600000011LL) == 1) << " method=" << (need > (1LL << 30) ? string("out-of-memory") : string("1")) << '\n';
    // N2: pairs of positions in 1 2 4 5 whose sum is divisible by 3. The method counts pairs that are both divisible by 3.
    vector<int> c = {1, 2, 4, 5};
    int bruteSum = 0, both = 0;
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) {
        bruteSum += (c[i] + c[j]) % 3 == 0;
        both += c[i] % 3 == 0 && c[j] % 3 == 0;
    }
    cout << "N2 brute=" << bruteSum << " method=" << both << '\n';
}
