#include <bits/stdc++.h>
using namespace std;

pair<int, long long> table(const vector<int>& coins, int x) {  // {fewest coins or -1, multisets}
    const int INF = INT_MAX / 2;
    vector<int> fewest(x + 1, INF);
    vector<long long> ways(x + 1, 0);
    fewest[0] = 0;
    ways[0] = 1;
    for (int c : coins) for (int s = c; s <= x; s++) { fewest[s] = min(fewest[s], fewest[s - c] + 1); ways[s] += ways[s - c]; }
    return {fewest[x] >= INF ? -1 : fewest[x], ways[x]};
}
int bruteFewest(const vector<int>& coins, int x) {
    int best = -1;
    function<void(int, int, int)> go = [&](int i, int left, int used) {
        if (i == (int)coins.size()) { if (left == 0 && (best == -1 || used < best)) best = used; return; }
        for (int k = 0; k * coins[i] <= left; k++) go(i + 1, left - k * coins[i], used + k);
    };
    go(0, x, 0);
    return best;
}
long long bruteMultisets(const vector<int>& coins, int x) {
    long long count = 0;
    function<void(int, int)> go = [&](int i, int left) {
        if (i == (int)coins.size()) { count += left == 0; return; }
        for (int k = 0; k * coins[i] <= left; k++) go(i + 1, left - k * coins[i]);
    };
    go(0, x);
    return count;
}
int main() {
    // P1: the multisets of the coins 1 and 2 that pay 3. P2: the fewest coins of 1, 5, 6 that pay 11. Brute: try every count of each coin.
    cout << "P1 brute=" << bruteMultisets({1, 2}, 3) << " method=" << table({1, 2}, 3).second << '\n';
    cout << "P2 brute=" << bruteFewest({1, 5, 6}, 11) << " method=" << table({1, 5, 6}, 11).first << '\n';
    // N1: the fewest coins to pay 6 with ONE coin of value 3 (each coin at most once), using the upward loop.
    cout << "N1 brute=" << -1 << " method=" << table({3}, 6).first << '\n';
    // N2: the fewest coins of 1, 5, 10, 25 for 10^18; the table would have 10^18 entries, the greedy count is 4 * 10^16.
    long long amount = 1000000000000000000LL;
    cout << "N2 brute=" << amount / 25 << " method=" << (amount > 100000000LL ? "too-slow" : "ok") << '\n';
}
