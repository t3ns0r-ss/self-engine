#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.5. Trial division: divide out each d while d*d <= n; the leftover n > 1 is a prime.
vector<long long> primeFactors(long long n) {
    vector<long long> primes;  // with repetition, increasing
    for (long long d = 2; d * d <= n; d++)
        while (n % d == 0) primes.push_back(d), n /= d;
    if (n > 1) primes.push_back(n);  // the leftover is a prime factor, possibly larger than sqrt of the original n
    return primes;
}
// snippet:end

void show(long long n) {
    cout << n << " =";
    for (long long p : primeFactors(n)) cout << ' ' << p;
    cout << '\n';
}
int main() {
    show(360);
    show(999999999989LL);
    show(1000000000000LL);
    show(2LL * 999983);
    for (long long n = 2; n <= 3000; n++) {
        auto ps = primeFactors(n);
        long long prod = 1;
        for (long long p : ps) {
            prod *= p;
            for (long long d = 2; d * d <= p; d++) if (p % d == 0) return 1;  // every recorded number is prime
        }
        if (prod != n || !is_sorted(ps.begin(), ps.end())) return 1;
    }
}
