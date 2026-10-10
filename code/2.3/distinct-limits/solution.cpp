/*
Problem: count the sequences A_1..A_n of pairwise different integers with 1 <= A_i <= C_i.
Input: n (1 <= n <= 2*10^5), then C_1 .. C_n (1 <= C_i <= 10^9).
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.1. Sequences of pairwise different integers with 1 <= A_i <= C_i: fill the most limited position first,
// so position i always has C_i - i options, whichever smaller values were taken.
long long distinctLimits(vector<long long> c) {
    const long long MOD = 1000000007;
    sort(c.begin(), c.end());
    long long ways = 1;
    for (int i = 0; i < (int)c.size(); i++) {
        long long options = c[i] - i;  // i smaller values are already taken, all within [1, c[i]]
        if (options <= 0) return 0;
        ways = ways * (options % MOD) % MOD;
    }
    return ways;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> c(n);
    for (auto& x : c) cin >> x;
    cout << distinctLimits(c) << "\n";
}
