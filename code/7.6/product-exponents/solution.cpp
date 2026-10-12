#include <bits/stdc++.h>
using namespace std;

/*
Problem: f_n = c^(2n - 6) * f_(n-1) * f_(n-2) * f_(n-3) for n >= 4. Given n (up to 10^18), f_1, f_2, f_3 and c (all up to 10^9), print f_n modulo
10^9 + 7.
Input: n, f_1, f_2, f_3, c.
Output: f_n modulo 10^9 + 7.
*/

const long long P = 1000000007;
using Matrix = vector<vector<long long>>;
Matrix multiply(const Matrix& a, const Matrix& b, long long mod) {
    int n = a.size();
    Matrix c(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
    return c;
}
Matrix power(Matrix base, long long e, long long mod) {  // base^e: start from the identity, then repeated squaring
    int n = base.size();
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1 % mod;
    for (; e > 0; e >>= 1, base = multiply(base, base, mod))
        if (e & 1) result = multiply(result, base, mod);
    return result;
}

// Theorem 7.6.1 (outside the shown code)
long long nthTerm(const vector<long long>& coef, const vector<long long>& init, long long n, long long mod) {
    int k = coef.size();
    Matrix c(k, vector<long long>(k, 0));
    for (int j = 0; j < k; j++) c[0][j] = coef[j] % mod;
    for (int i = 1; i < k; i++) c[i][i - 1] = 1;
    Matrix p = power(c, n, mod);  // v_0 = (x_{k-1}, ..., x_0), and x_n is the last entry of C^n v_0
    long long result = 0;
    for (int j = 0; j < k; j++) result = (result + p[k - 1][j] * (init[k - 1 - j] % mod)) % mod;
    return result;
}

long long powMod(long long b, long long e, long long m) {
    long long r = 1;
    for (b %= m; e > 0; e >>= 1, b = b * b % m)
        if (e & 1) r = r * b % m;
    return r;
}
// snippet:begin
// Theorem 7.6.3 (a) with the exponents: g_n = c^n f_n satisfies g_n = g_(n-1) g_(n-2) g_(n-3), so g_n = g_1^a * g_2^b * g_3^d where a, b, d follow
// the tribonacci recurrence. P is a prime and g_i is not divisible by it, so the exponents are kept modulo P - 1 (Fermat's little theorem).
long long product(long long n, long long f1, long long f2, long long f3, long long c) {
    long long a = nthTerm({1, 1, 1}, {1, 0, 0}, n - 1, P - 1);  // the exponent of g_1 in g_n (index n - 1 from 0)
    long long b = nthTerm({1, 1, 1}, {0, 1, 0}, n - 1, P - 1);
    long long d = nthTerm({1, 1, 1}, {0, 0, 1}, n - 1, P - 1);
    long long g = powMod(c * f1 % P, a, P) * powMod(c * c % P * f2 % P, b, P) % P * powMod(powMod(c, 3, P) * f3 % P, d, P) % P;
    return g * powMod(powMod(c, n % (P - 1), P), P - 2, P) % P;  // f_n = g_n / c^n
}
// snippet:end

int main() {
    long long n, f1, f2, f3, c;
    cin >> n >> f1 >> f2 >> f3 >> c;
    cout << product(n, f1, f2, f3, c) << "\n";
}
