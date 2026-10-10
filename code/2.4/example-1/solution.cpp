/*
Problem: AtCoder ABC 326 E, Revenge of "The Salary of AtCoder Inc.".
Input: N (1 <= N <= 3*10^5), then A_1 .. A_N (0 <= A_i < 998244353).
Output: the expected salary modulo 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
const long long MOD = 998244353;
long long power(long long a, long long b) {
    long long r = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}
// ABC 326 E. A_y is paid with probability (1/N)(1 + 1/N)^(y-1); by linearity the expected salary is the sum of A_y * P.
long long expectedSalary(const vector<long long>& A) {
    long long n = A.size();
    long long invN = power(n, MOD - 2), grow = (1 + invN) % MOD, pwr = 1, e = 0;
    for (long long y = 1; y <= n; y++) {
        long long p = invN * pwr % MOD;
        e = (e + A[y - 1] % MOD * p) % MOD;
        pwr = pwr * grow % MOD;
    }
    return e;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> A(n);
    for (auto& x : A) cin >> x;
    cout << expectedSalary(A) << "\n";
}
