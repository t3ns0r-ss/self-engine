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
long long sigmaBrute(long long n) {
    long long s = 0;
    for (long long d = 1; d <= n; d++) if (n % d == 0) s += d;
    return s;
}
map<long long, int> factorise(long long n) {
    map<long long, int> f;
    for (long long d = 2; d * d <= n; d++) while (n % d == 0) f[d]++, n /= d;
    if (n > 1) f[n]++;
    return f;
}
int main() {
    // P1: d(360). P2: sigma(720). Brute: loop over all d. Method: trial division, then the product formulas.
    long long cnt = 1;
    for (auto [p, e] : factorise(360)) cnt *= e + 1;
    cout << "P1 brute=" << divisorsBrute(360) << " method=" << cnt << '\n';
    long long sum = 1;
    for (auto [p, e] : factorise(720)) {
        long long term = 1, pw = 1;
        for (int k = 1; k <= e; k++) pw *= p, term += pw;
        sum *= term;
    }
    cout << "P2 brute=" << sigmaBrute(720) << " method=" << sum << '\n';
    // N1: the number of divisors of 999999937^2, about 10^18. 999999937 is prime (checked here), so d = 3.
    // Trial division of n itself needs sqrt(n) = 999999937 steps, far above the budget.
    long long p = 999999937;
    bool prime = true;
    for (long long d = 2; d * d <= p; d++) if (p % d == 0) prime = false;
    long long steps = p;  // d runs up to sqrt(p * p)
    cout << "N1 brute=" << (prime ? 3 : 0) << " method=" << (steps > 300000000 ? "too-slow" : "ok") << '\n';
}
