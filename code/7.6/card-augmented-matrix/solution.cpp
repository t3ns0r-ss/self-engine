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

// Theorem 7.6.3 (a). x_{n+1} = a x_n + b: on the vector (x_n, 1) the matrix is [[a, b], [0, 1]]. Returns x_n.
long long affineTerm(long long a, long long b, long long x0, long long n, long long mod) {
    Matrix p = power({{a % mod, b % mod}, {0, 1}}, n, mod);
    return (p[0][0] * (x0 % mod) + p[0][1]) % mod;
}
// Theorem 7.6.3 (b). S_n = x_0 + ... + x_{n-1} for the recurrence with the coefficients `coef`: on (S_n, v_n) the matrix is [[1, e], [0, C]],
// where e picks x_n, the last entry of v_n, and C is the companion matrix of Theorem 7.6.1.
long long prefixSum(const vector<long long>& coef, const vector<long long>& init, long long n, long long mod) {
    int k = coef.size();
    Matrix c(k + 1, vector<long long>(k + 1, 0));
    c[0][0] = 1;
    c[0][k] = 1;
    for (int j = 0; j < k; j++) c[1][1 + j] = coef[j] % mod;
    for (int i = 2; i <= k; i++) c[i][i - 1] = 1;
    Matrix p = power(c, n, mod);  // the start vector is (0, x_{k-1}, ..., x_0)
    long long result = 0;
    for (int j = 0; j < k; j++) result = (result + p[0][1 + j] * (init[k - 1 - j] % mod)) % mod;
    return result;
}

int main() {
    // P1: x_0 = 1, x_n = 2 x_{n-1} + 3: x_30 mod 1000
    long long x = 1;
    for (int n = 1; n <= 30; n++) x = (2 * x + 3) % 1000;
    cout << "P1 brute=" << x << " method=" << affineTerm(2, 3, 1, 30, 1000) << "\n";
    // P2: F_0 + ... + F_49 mod 1000
    long long a = 0, b = 1, sum = 0;
    for (int i = 0; i < 50; i++) sum = (sum + a) % 1000, tie(a, b) = make_pair(b, (a + b) % 1000);
    cout << "P2 brute=" << sum << " method=" << prefixSum({1, 1}, {0, 1}, 50, 1000) << "\n";
    // N1: x_0 = 0, x_n = x_{n-1} + (n mod 3): x_6, against the matrix for x_n = x_{n-1} + n
    long long y = 0;
    for (int n = 1; n <= 6; n++) y += n % 3;
    // the matrix on (x_n, n + 1, 1): x_{n+1} = x_n + (n + 1), n + 2 = (n + 1) + 1
    Matrix p = power({{1, 1, 0}, {0, 1, 1}, {0, 0, 1}}, 6, MOD);
    long long wrong = (p[0][0] * 0 + p[0][1] * 1 + p[0][2] * 1) % MOD;
    cout << "N1 brute=" << y << " method=" << wrong << "\n";
    // N2: x_0 = 1, x_n = n x_{n-1}: x_5, against the matrix with the fixed coefficient 5
    long long z = 1;
    for (int n = 1; n <= 5; n++) z *= n;
    cout << "N2 brute=" << z << " method=" << affineTerm(5, 0, 1, 5, MOD) << "\n";
}
