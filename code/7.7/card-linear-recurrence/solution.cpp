#include <bits/stdc++.h>
using namespace std;

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

// brute: a plain loop over the terms.
long long loopTerm(const vector<long long>& coef, const vector<long long>& init, int n, long long mod) {
    vector<long long> x(init.begin(), init.end());
    for (int i = coef.size(); i <= n; i++) {
        long long next = 0;
        for (size_t j = 0; j < coef.size(); j++) next = (next + coef[j] * x[i - 1 - j]) % mod;
        x.push_back(next);
    }
    return x[n];
}
int main() {
    // P1: x_0 = 0, x_1 = 1, x_n = x_{n-1} + x_{n-2}: x_100 mod 10^9 + 7
    cout << "P1 brute=" << loopTerm({1, 1}, {0, 1}, 100, MOD) << " method=" << nthTerm({1, 1}, {0, 1}, 100, MOD) << "\n";
    // P2: x_0 = 1, x_1 = 1, x_n = 2 x_{n-1} + 3 x_{n-2}: x_30 mod 1000
    cout << "P2 brute=" << loopTerm({2, 3}, {1, 1}, 30, 1000) << " method=" << nthTerm({2, 3}, {1, 1}, 30, 1000) << "\n";
    // N1: D_0 = 1, D_1 = 0, D_n = (n - 1)(D_{n-1} + D_{n-2}) (derangements): D_10 exactly, against a matrix with the fixed coefficient 9
    vector<long long> d = {1, 0};
    for (int n = 2; n <= 10; n++) d.push_back((n - 1) * (d[n - 1] + d[n - 2]));
    cout << "N1 brute=" << d[10] << " method=" << nthTerm({9, 9}, {1, 0}, 10, MOD) << "\n";
}
