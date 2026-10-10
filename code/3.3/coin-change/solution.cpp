/*
Problem: coins of m distinct values, unlimited supply of each. For the amount x, print the fewest coins that pay
exactly x (or -1), and the number of different multisets of coins that pay x (order ignored), modulo 10^9 + 7.
Input: m x (1 <= m <= 100, 1 <= x <= 10^6), then m distinct coin values (1 <= c_j <= 10^6).
Output: the fewest coins (or -1), then the number of ways.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.3. Unlimited coins: the amount loop runs upwards. With the coin loop outside, each multiset is counted once.
pair<int, long long> coinChange(const vector<int>& coin, int x) {
    const long long MOD = 1000000007;
    const int INF = INT_MAX / 2;  // "cannot be paid"; INF + 1 does not overflow
    vector<int> fewest(x + 1, INF);
    vector<long long> ways(x + 1, 0);
    fewest[0] = 0;
    ways[0] = 1;  // the empty multiset
    for (int c : coin)
        for (int s = c; s <= x; s++) {
            fewest[s] = min(fewest[s], fewest[s - c] + 1);
            ways[s] = (ways[s] + ways[s - c]) % MOD;
        }
    return {fewest[x] >= INF ? -1 : fewest[x], ways[x]};
}
// snippet:end

int main() {
    int m, x;
    cin >> m >> x;
    vector<int> coin(m);
    for (int& c : coin) cin >> c;
    auto [fewest, ways] = coinChange(coin, x);
    cout << fewest << "\n" << ways << "\n";
}
