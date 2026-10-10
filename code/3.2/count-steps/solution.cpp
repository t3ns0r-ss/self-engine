/*
Problem: count the ordered ways to climb n stairs when each step climbs one of the m given amounts s_1..s_m,
modulo 10^9 + 7.
Input: n m (1 <= n <= 10^6, 1 <= m <= 10), then m distinct amounts (1 <= s_j <= n).
Output: the number of ways modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.2. ways[i] = the step sequences that reach stair i exactly: split by the last step.
long long countSteps(int n, const vector<int>& s) {
    const long long MOD = 1000000007;
    vector<long long> ways(n + 1, 0);
    ways[0] = 1;  // base case: the empty sequence
    for (int i = 1; i <= n; i++)
        for (int step : s)
            if (step <= i) ways[i] = (ways[i] + ways[i - step]) % MOD;
    return ways[n];
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> s(m);
    for (int& x : s) cin >> x;
    cout << countSteps(n, s) << "\n";
}
