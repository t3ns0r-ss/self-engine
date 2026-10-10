#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.4. spf[x] = the smallest prime factor of x; then x splits into primes by repeated division.
vector<int> buildSpf(int N) {
    vector<int> spf(N + 1, 0);
    for (int p = 2; p <= N; p++) {
        if (spf[p] != 0) continue;  // p is prime
        spf[p] = p;
        for (long long j = (long long)p * p; j <= N; j += p)
            if (spf[j] == 0) spf[j] = p;
    }
    return spf;
}
vector<int> primesOf(int x, const vector<int>& spf) {
    vector<int> primes;
    while (x > 1) primes.push_back(spf[x]), x /= spf[x];  // increasing order, at most log2(x) steps
    return primes;
}
// snippet:end

int main() {
    vector<int> spf = buildSpf(1000);
    cout << "spf(45) = " << spf[45] << ", spf(13) = " << spf[13] << '\n';
    cout << "360 splits into:";
    for (int p : primesOf(360, spf)) cout << ' ' << p;
    cout << " (" << primesOf(360, spf).size() << " divisions)\n";
    for (int x = 2; x <= 1000; x++) {
        int smallest = x;
        for (int d = 2; d < x; d++) if (x % d == 0) { smallest = d; break; }
        auto ps = primesOf(x, spf);
        long long prod = 1;
        for (int p : ps) prod *= p;
        if (spf[x] != smallest || prod != x || !is_sorted(ps.begin(), ps.end()) || (1 << ps.size()) > 2 * x) return 1;
    }
}
