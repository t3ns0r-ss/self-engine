#include <bits/stdc++.h>
using namespace std;

/*
Problem: the arithmetic progression A, A + B, ..., A + (L - 1) B (all terms below 10^18) written one after another in base ten without
spaces is a big number; print it modulo M.
Input: L, A, B and M (L, A, B up to 10^18, 2 <= M <= 10^9).
Output: the remainder.
*/

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
// Theorem 7.6.3: appending a term s with d digits is X := X * 10^d + s, and the next term is s + B. On the vector (X, s, 1) the step is the
// matrix below. The terms with the same number of digits are a block, so for d = 1 ... 18 raise the step of that d to the block length.
long long concatenated(long long L, long long A, long long B, long long M) {
    auto countBelow = [&](long long limit) {  // the number of terms smaller than limit
        return limit <= A ? 0 : min(L, (limit - A - 1) / B + 1);
    };
    vector<long long> v = {0, A % M, 1};
    long long ten = 1;  // 10^(d-1)
    for (int d = 1; d <= 18; d++) {
        long long count = countBelow(ten * 10) - countBelow(ten);
        Matrix step = {{ten * 10 % M, 1, 0}, {0, 1, B % M}, {0, 0, 1}};
        Matrix p = power(step, count, M);
        vector<long long> next(3, 0);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) next[i] = (next[i] + p[i][j] * v[j]) % M;
        v = next;
        ten *= 10;
    }
    return v[0];
}
// snippet:end

int main() {
    long long L, A, B, M;
    cin >> L >> A >> B >> M;
    cout << concatenated(L, A, B, M) << "\n";
}
