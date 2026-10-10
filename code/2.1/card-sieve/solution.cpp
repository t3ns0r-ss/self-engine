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
int main() {
    // P1: the number of primes up to 30. Brute: trial division of each. Method: the sieve.
    int brute = 0;
    for (int x = 2; x <= 30; x++) {
        bool p = true;
        for (int d = 2; d * d <= x; d++) if (x % d == 0) p = false;
        brute += p;
    }
    auto f = sieve(30);
    cout << "P1 brute=" << brute << " method=" << count(f.begin(), f.end(), true) << '\n';
    // N1: the number of divisors of 36, read from the sieve flags as "the primes that divide 36".
    auto g = sieve(36);
    int method = 0;
    for (int p = 2; p <= 36; p++) if (g[p] && 36 % p == 0) method++;
    cout << "N1 brute=" << divisorsBrute(36) << " method=" << method << '\n';
}
