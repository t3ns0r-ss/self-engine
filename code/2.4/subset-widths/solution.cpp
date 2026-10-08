/*
Problem: the sum of (maximum - minimum) over all non-empty subsets of an array.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (1 <= a_i <= 10^9).
Output: the sum modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 1000000007;
    int n;
    cin >> n;
    vector<long long> a(n), pw(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());
    pw[0] = 1;
    for (int i = 1; i < n; i++) pw[i] = pw[i - 1] * 2 % MOD;
    long long total = 0;
    for (int i = 0; i < n; i++) {
        // after sorting (ties broken by position), a[i] is the maximum of 2^i subsets
        // and the minimum of 2^(n-1-i) subsets  (Theorem 2.4.3)
        long long c = (pw[i] - pw[n - 1 - i] + MOD) % MOD;
        total = (total + a[i] % MOD * c) % MOD;
    }
    cout << total << "\n";
}
