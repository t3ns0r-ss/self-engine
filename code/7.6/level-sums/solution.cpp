#include <bits/stdc++.h>
using namespace std;

/*
Problem: every vertex of an infinite tree has n children, connected by edges of the lengths d_1, ..., d_n (each at most 100). Count the
vertices at the distance at most x from the root (x up to 10^9), modulo 10^9 + 7.
Input: n and x, then d_1 ... d_n.
Output: the number of vertices modulo 10^9 + 7.
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

// Theorem 7.6.3 (b) (outside the shown code)
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

// snippet:begin
// Theorem 7.6.3 (b): f(i) = the number of vertices at the distance exactly i = sum over d of cnt[d] f(i - d), f(0) = 1. The answer is
// f(0) + ... + f(x) = S_{x+1}, the prefix sum of the recurrence of order D = 100. cnt[d] = the number of children at the length d.
long long treeSize(const vector<long long>& cnt, long long x) {  // cnt[1..D]
    int D = cnt.size() - 1;
    vector<long long> coef(cnt.begin() + 1, cnt.end()), init(D, 0);
    for (int i = 0; i < D; i++) {  // f(0) ... f(D-1) by the recurrence itself
        init[i] = i == 0 ? 1 : 0;
        for (int d = 1; d <= i; d++) init[i] = (init[i] + cnt[d] * init[i - d]) % MOD;
    }
    return prefixSum(coef, init, x + 1, MOD);
}
// snippet:end

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> cnt(101, 0);
    for (int i = 0; i < n; i++) {
        int d;
        cin >> d;
        cnt[d]++;
    }
    cout << treeSize(cnt, x) << "\n";
}
