/*
Problem: count the ways to write n as a sum of allowed parts that use at least one part >= d,
modulo 10^9 + 7. With t = 0, order matters (1 + 2 and 2 + 1 differ); with t = 1 it does not.
Input: t n d m (1 <= n <= 10^5, 1 <= d <= n, 1 <= m <= 100), then m distinct allowed parts (1 <= part <= n).
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;
int t, n;

// the number of sums of n using only the given parts
long long countSums(const vector<int>& parts) {
    vector<long long> f(n + 1, 0);
    f[0] = 1;  // the empty sum
    if (t == 0) {
        for (int total = 1; total <= n; total++)       // ordered: totals outside,
            for (int p : parts)                        // split by the last part (Theorem 3.5.1)
                if (p <= total) f[total] = (f[total] + f[total - p]) % MOD;
    } else {
        for (int p : parts)                            // unordered: parts outside (Theorem 3.3.3)
            for (int total = p; total <= n; total++) f[total] = (f[total] + f[total - p]) % MOD;
    }
    return f[n];
}

int main() {
    int d, m;
    cin >> t >> n >> d >> m;
    vector<int> parts(m), small;
    for (int& p : parts) cin >> p;
    for (int p : parts)
        if (p < d) small.push_back(p);
    // all sums minus the sums with no part >= d (Theorem 3.5.3)
    cout << (countSums(parts) - countSums(small) + MOD) % MOD << "\n";
}
