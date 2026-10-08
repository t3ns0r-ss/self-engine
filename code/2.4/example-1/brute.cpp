#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
long long n, invN;
vector<long long> A;

// Expected further salary from state x, by trying every roll (the process stops within n + 1 rolls).
long long walk(long long x, long long prob) {
    long long total = 0;
    for (long long y = 1; y <= n; y++) {
        if (y <= x) continue;  // this roll ends the process: no more pay
        long long p = prob * invN % MOD;
        total = (total + p * A[y] % MOD + walk(y, p)) % MOD;
    }
    return total;
}

int main() {
    cin >> n;
    A.assign(n + 1, 0);
    for (long long i = 1; i <= n; i++) cin >> A[i];
    invN = 1;
    for (long long e = MOD - 2, b = n; e > 0; e >>= 1, b = b * b % MOD)
        if (e & 1) invN = invN * b % MOD;
    cout << walk(0, 1) << "\n";
}
