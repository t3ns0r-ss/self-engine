#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 7.6.1. x_n = c_1 x_{n-1} + ... + c_k x_{n-k} (mod m). The vector v_n = (x_{n+k-1}, ..., x_n) satisfies v_{n+1} = C v_n, where
// the first row of C is c_1 ... c_k and C has 1 just below the diagonal. So v_n = C^n v_0, and x_n is the last entry of v_n.
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
// snippet:end

long long bruteTerm(const vector<long long>& coef, const vector<long long>& init, int n, long long mod) {
    vector<long long> x(init.begin(), init.end());
    int k = coef.size();
    for (int i = k; i <= n; i++) {
        long long next = 0;
        for (int j = 0; j < k; j++) next = (next + coef[j] * x[i - 1 - j]) % mod;
        x.push_back(next);
    }
    return x[n] % mod;
}

int main() {
    const long long MOD = 1000000007;
    cout << "x_10 = " << nthTerm({1, 1}, {0, 1}, 10, MOD) << " for x_n = x_{n-1} + x_{n-2}, x_0 = 0, x_1 = 1\n";
    cout << "x_11 = " << nthTerm({1, 1, 1}, {0, 0, 1}, 11, MOD) << " for x_n = x_{n-1} + x_{n-2} + x_{n-3}, x_0 = 0, x_1 = 0, x_2 = 1\n";
    cout << "x_(10^18) mod 1000000007 = " << nthTerm({1, 1}, {0, 1}, 1000000000000000000LL, MOD) << " for x_n = x_{n-1} + x_{n-2}, x_0 = 0, x_1 = 1\n";
    // Check (not printed): every recurrence of order 1 to 3 with coefficients and starting values in {0, 1, 2}, n up to 40, modulus 1000.
    for (int k = 1; k <= 3; k++) {
        int combos = 1;
        for (int i = 0; i < 2 * k; i++) combos *= 3;
        for (int code = 0; code < combos; code++) {
            vector<long long> coef(k), init(k);
            int c = code;
            for (int j = 0; j < k; j++, c /= 3) coef[j] = c % 3;
            for (int j = 0; j < k; j++, c /= 3) init[j] = c % 3;
            for (int n = 0; n <= 40; n++)
                if (nthTerm(coef, init, n, 1000) != bruteTerm(coef, init, n, 1000)) return 1;
        }
    }
}
