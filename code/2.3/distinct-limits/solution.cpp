/*
Problem: count the sequences A_1..A_n of pairwise different integers with 1 <= A_i <= C_i.
Input: n (1 <= n <= 2*10^5), then C_1 .. C_n (1 <= C_i <= 10^9).
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 1000000007;
    int n;
    cin >> n;
    vector<long long> c(n);
    for (auto& x : c) cin >> x;
    sort(c.begin(), c.end());  // choose the most limited position first
    long long ways = 1;
    for (int i = 0; i < n; i++) {
        long long options = c[i] - i;  // i smaller values are already taken, all within [1, c[i]]
        if (options <= 0) {
            ways = 0;
            break;
        }
        ways = ways * (options % MOD) % MOD;  // product rule (Theorem 2.3.1)
    }
    cout << ways << "\n";
}
