#include <bits/stdc++.h>
using namespace std;

/*
Problem: a magic gem takes 1 unit of space; it can be split into M normal gems, which take M units. Count the configurations (sets of gems,
each either magic and kept, or magic and split) that fill exactly N units, modulo 10^9 + 7. Two configurations differ if the gems differ
in number or in which ones are split.
Input: N and M (N up to 10^18, 2 <= M <= 100).
Output: the number of configurations modulo 10^9 + 7.
*/

const long long MOD = 1000000007;
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

// Theorem 7.6.1 for the recurrence of Theorem 7.6.1 (outside the shown code)
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

// snippet:begin
// Theorem 7.6.1 with a sparse recurrence: f(n) = f(n - 1) + f(n - m), f(0) = ... = f(m - 1) = 1 (a gem is magic and kept, or split).
long long magicGems(long long n, int m) {
    vector<long long> coef(m, 0), init(m, 1);
    coef[0] = 1;      // f(n - 1)
    coef[m - 1] = 1;  // f(n - m)
    return nthTerm(coef, init, n, MOD);
}
// snippet:end

int main() {
    long long n;
    int m;
    cin >> n >> m;
    cout << magicGems(n, m) << "\n";
}
