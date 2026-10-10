/*
Problem: the sum of (maximum - minimum) over all non-empty subsets of an array.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (1 <= a_i <= 10^9).
Output: the sum modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.4.3. The sum of (max - min) over all non-empty subsets: after sorting, a[i] is the maximum of 2^i subsets
// and the minimum of 2^(n-1-i) subsets.
long long subsetWidths(vector<long long> a) {
    const long long MOD = 1000000007;
    int n = a.size();
    sort(a.begin(), a.end());
    vector<long long> pw(n);
    pw[0] = 1;
    for (int i = 1; i < n; i++) pw[i] = pw[i - 1] * 2 % MOD;
    long long total = 0;
    for (int i = 0; i < n; i++) total = (total + a[i] % MOD * ((pw[i] - pw[n - 1 - i] + MOD) % MOD)) % MOD;
    return total;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << subsetWidths(a) << "\n";
}
