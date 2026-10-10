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
vector<int> buildSpf(int N) {
    vector<int> spf(N + 1, 0);
    for (int p = 2; p <= N; p++) {
        if (spf[p] != 0) continue;
        spf[p] = p;
        for (long long j = (long long)p * p; j <= N; j += p) if (spf[j] == 0) spf[j] = p;
    }
    return spf;
}
string divisorsBySpf(int v, const vector<int>& spf) {
    if (v >= (int)spf.size()) return "out-of-range";  // the table has no entry for v
    int d = 1;
    while (v > 1) {
        int p = spf[v], e = 0;
        while (v % p == 0) v /= p, e++;
        d *= e + 1;
    }
    return to_string(d);
}
int main() {
    // P1: the number of divisors of 360. Brute: count them. Method: the table.
    auto spf = buildSpf(1000000);
    cout << "P1 brute=" << divisorsBrute(360) << " method=" << divisorsBySpf(360, spf) << '\n';
    // N1: the number of divisors of 2000006 = 2 * 1000003, with a table that only reaches 10^6.
    cout << "N1 brute=" << divisorsBrute(2000006) << " method=" << divisorsBySpf(2000006, spf) << '\n';
}
