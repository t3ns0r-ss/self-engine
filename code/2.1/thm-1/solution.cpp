#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.1. Cross off the multiples of each prime p, starting at p*p; the unmarked numbers >= 2 are the primes.
vector<bool> sieve(int N) {
    vector<bool> isPrime(N + 1, true);
    isPrime[0] = false;
    if (N >= 1) isPrime[1] = false;
    for (int p = 2; (long long)p * p <= N; p++)
        if (isPrime[p])
            for (int j = p * p; j <= N; j += p) isPrime[j] = false;
    return isPrime;
}
// snippet:end

int main() {
    auto isPrime = sieve(30);
    cout << "primes up to 30:";
    for (int x = 0; x <= 30; x++) if (isPrime[x]) cout << ' ' << x;
    cout << '\n';
    for (int N : {100, 1000000}) {
        auto f = sieve(N);
        cout << "primes up to " << N << ": " << count(f.begin(), f.end(), true) << '\n';
    }
    auto f = sieve(3000);
    for (int x = 0; x <= 3000; x++) {
        bool p = x >= 2;
        for (int d = 2; d * d <= x; d++) if (x % d == 0) p = false;
        if (p != f[x]) return 1;
    }
}
