#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1096 Throwing Dice. Count the ways to get the sum n by throwing a die (1 ... 6) several times (the order matters), modulo 10^9 + 7.
Input: n (up to 10^18).
Output: the number of ways modulo 10^9 + 7.
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

// snippet:begin
// Theorem 7.6.1 with k = 6: f(n) = f(n-1) + ... + f(n-6), f(0) = 1 and f(1..5) = 1, 2, 4, 8, 16 (the sum of the previous ones).
long long diceWays(long long n) {
    return nthTerm({1, 1, 1, 1, 1, 1}, {1, 1, 2, 4, 8, 16}, n, MOD);
}
// snippet:end

int main() {
    long long n;
    cin >> n;
    cout << diceWays(n) << "\n";
}
