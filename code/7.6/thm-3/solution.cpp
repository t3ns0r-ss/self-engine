#include <bits/stdc++.h>
using namespace std;

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

// snippet:begin
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
// snippet:end

int main() {
    const long long MOD = 1000000007;
    cout << "x_n = 2 x_{n-1} + 3, x_0 = 1: x_4 = " << affineTerm(2, 3, 1, 4, MOD) << "\n";
    cout << "Fibonacci: S_10 = F_0 + ... + F_9 = " << prefixSum({1, 1}, {0, 1}, 10, MOD) << "\n";
    cout << "Fibonacci: S_0 = " << prefixSum({1, 1}, {0, 1}, 0, MOD) << "\n";
    // Check (not printed): loops for all small affine maps and all recurrences of order 1 to 3 with coefficients and starting values in {0, 1, 2}.
    for (int a = 0; a < 4; a++)
        for (int b = 0; b < 4; b++)
            for (int x0 = 0; x0 < 4; x0++) {
                long long x = x0;
                for (int n = 0; n <= 30; n++, x = (a * x + b) % 1000)
                    if (affineTerm(a, b, x0, n, 1000) != x) return 1;
            }
    for (int k = 1; k <= 3; k++) {
        int combos = 1;
        for (int i = 0; i < 2 * k; i++) combos *= 3;
        for (int code = 0; code < combos; code++) {
            vector<long long> coef(k), init(k);
            int c = code;
            for (int j = 0; j < k; j++, c /= 3) coef[j] = c % 3;
            for (int j = 0; j < k; j++, c /= 3) init[j] = c % 3;
            vector<long long> x(init.begin(), init.end());
            for (int i = k; i <= 40; i++) {
                long long next = 0;
                for (int j = 0; j < k; j++) next = (next + coef[j] * x[i - 1 - j]) % 1000;
                x.push_back(next);
            }
            long long sum = 0;
            for (int n = 0; n <= 40; n++, sum = (sum + x[n - 1]) % 1000)
                if (prefixSum(coef, init, n, 1000) != sum) return 1;
        }
    }
}
