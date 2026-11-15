#include <bits/stdc++.h>
using namespace std;

long long power(long long a, long long b, long long m) {
    long long r = 1 % m;
    a %= m;
    while (b > 0) { if (b & 1) r = r * a % m; a = a * a % m; b >>= 1; }
    return r;
}
// the factorial-table formula f_n * g_r * g_(n-r) modulo m, with the inverse factorials by Fermat (a prime m is assumed)
long long tableBinom(int n, int r, long long m) {
    auto fact = [&](int k) { long long f = 1 % m; for (int i = 1; i <= k; i++) f = f * i % m; return f; };
    return fact(n) * power(fact(r), m - 2, m) % m * power(fact(n - r), m - 2, m) % m;
}
long long pascal(int n, int r, long long m) {
    vector<vector<long long>> C(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i <= n; i++) { C[i][0] = 1 % m; for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % m; }
    return C[n][r];
}
int main() {
    // P1: the strings of length 6 with exactly 2 letters a and 4 letters b. Brute: list all 64 strings. Method: C(6, 2).
    int brute = 0;
    for (int mask = 0; mask < 64; mask++) brute += __builtin_popcount(mask) == 2;
    cout << "P1 brute=" << brute << " method=" << tableBinom(6, 2, 1000000007) << '\n';
    // N1: C(14, 7) modulo 7. The prime 7 is below n, so 14! is a multiple of 7 and the table formula collapses.
    cout << "N1 brute=" << pascal(14, 7, 7) << " method=" << tableBinom(14, 7, 7) << '\n';
    // N2: C(6, 3) modulo 8, which is not prime: the "inverse factorials" 6^(8-2) mod 8 are not inverses.
    cout << "N2 brute=" << pascal(6, 3, 8) << " method=" << tableBinom(6, 3, 8) << '\n';
}
