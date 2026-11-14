#include <bits/stdc++.h>
using namespace std;

long long power(long long a, long long b, long long m) {
    long long r = 1 % m;
    a %= m;
    while (b > 0) { if (b & 1) r = r * a % m; a = a * a % m; b >>= 1; }
    return r;
}
// the factorial-table formula of Theorem 2.3.3 applied to any n (Fermat inverses, so a prime m is assumed)
long long tableBinom(int n, int r, long long m) {
    auto fact = [&](int k) { long long f = 1 % m; for (int i = 1; i <= k; i++) f = f * i % m; return f; };
    return fact(n) * power(fact(r), m - 2, m) % m * power(fact(n - r), m - 2, m) % m;
}
long long pascal(int n, int r, long long m) {
    vector<vector<long long>> C(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i <= n; i++) { C[i][0] = 1 % m; for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % m; }
    return C[n][r];
}
// Lucas with digits of the modulus m taken as if m were prime (Theorem 2.3.8); the digit binomials come from Pascal's triangle
long long lucasDigits(long long n, long long r, int m) {
    long long res = 1 % m;
    for (; n > 0 || r > 0; n /= m, r /= m) {
        int a = n % m, b = r % m;
        res = res * (b > a ? 0 : pascal(a, b, m)) % m;
    }
    return res;
}
int main() {
    // P1: C(14, 7) modulo 7. Brute: Pascal's triangle with the modulus at each step. Method: Lucas, 14 = 20 and 7 = 10 in base 7.
    cout << "P1 brute=" << pascal(14, 7, 7) << " method=" << lucasDigits(14, 7, 7) << '\n';
    // P2: C(10, 3) modulo 2. Method: Lucas with p = 2 (10 = 1010 and 3 = 0011 in binary).
    cout << "P2 brute=" << pascal(10, 3, 2) << " method=" << lucasDigits(10, 3, 2) << '\n';
    // N1: C(4, 2) modulo 4, a prime power. Lucas with base-4 digits (4 = 10, 2 = 02) gives 0, the truth is 6 mod 4 = 2.
    cout << "N1 brute=" << pascal(4, 2, 4) << " method=" << lucasDigits(4, 2, 4) << '\n';
    // N2: C(9, 3) modulo 9, a prime power. Base-9 digits (9 = 10, 3 = 03) give 0, the truth is 84 mod 9 = 3.
    cout << "N2 brute=" << pascal(9, 3, 9) << " method=" << lucasDigits(9, 3, 9) << '\n';
    // Extra (not an example): the table formula of Theorem 2.3.3 on C(14, 7) modulo 7 collapses to 0 while Lucas gives 2.
    cout << "table formula on C(14, 7) mod 7 = " << tableBinom(14, 7, 7) << '\n';
}
