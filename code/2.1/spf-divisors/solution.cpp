/*
Problem: print the number of divisors of each of n numbers.
Input: n (1 <= n <= 2*10^5), then x_1 .. x_n (1 <= x_i <= 10^7).
Output: d(x_i) for each i, one per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.4. spf[x] = the smallest prime factor of x, for 2 <= x <= N.
vector<int> buildSpf(int N) {
    vector<int> spf(N + 1, 0);
    for (int p = 2; p <= N; p++) {
        if (spf[p] != 0) continue;  // p is prime
        spf[p] = p;
        if ((long long)p * p > N) continue;
        for (int j = p * p; j <= N; j += p)
            if (spf[j] == 0) spf[j] = p;
    }
    return spf;
}
// d(v) from the exponents of the primes that spf divides out (Theorem 2.1.3).
int divisorCount(int v, const vector<int>& spf) {
    int divisors = 1;
    while (v > 1) {
        int p = spf[v], e = 0;
        while (v % p == 0) v /= p, e++;  // the run of equal primes
        divisors *= e + 1;
    }
    return divisors;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto& v : x) cin >> v;
    vector<int> spf = buildSpf(max(2, *max_element(x.begin(), x.end())));
    for (int v : x) cout << divisorCount(v, spf) << "\n";
}
