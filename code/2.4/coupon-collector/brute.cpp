#include <bits/stdc++.h>
using namespace std;

// A different formula: P(not finished after t draws) by inclusion-exclusion over the missing kinds,
// summed over t: E = sum over j >= 1 of (-1)^(j+1) * C(n - c, j) * n / j.
int main() {
    const long long MOD = 998244353;
    long long n, c;
    cin >> n >> c;
    long long r = n - c;
    vector<vector<long long>> C(r + 1, vector<long long>(r + 1, 0));
    for (int i = 0; i <= r; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    auto inv = [&](long long a) {
        long long res = 1;
        for (long long e = MOD - 2; e > 0; e >>= 1, a = a * a % MOD)
            if (e & 1) res = res * a % MOD;
        return res;
    };
    long long e = 0;
    for (long long j = 1; j <= r; j++) {
        long long term = C[r][j] * (n % MOD) % MOD * inv(j) % MOD;
        e = (j % 2 == 1) ? (e + term) % MOD : (e - term + MOD) % MOD;
    }
    cout << e << "\n";
}
