#include <bits/stdc++.h>
using namespace std;

long long assignment(const vector<vector<long long>>& c) {
    int n = c.size();
    vector<long long> dp(1 << n, LLONG_MAX);
    dp[0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) for (int j = 0; j < n; j++)
        if (mask >> j & 1) dp[mask] = min(dp[mask], dp[mask ^ 1 << j] + c[__builtin_popcount(mask) - 1][j]);
    return dp[(1 << n) - 1];
}
int main() {
    // P1: the 3 x 3 cost matrix 4 1 3 / 2 0 5 / 3 2 2. Brute: all 6 assignments. Method: dp over masks of used jobs.
    vector<vector<long long>> c = {{4, 1, 3}, {2, 0, 5}, {3, 2, 2}};
    vector<int> p = {0, 1, 2};
    long long best = LLONG_MAX;
    do { long long s = 0; for (int i = 0; i < 3; i++) s += c[i][p[i]]; best = min(best, s); } while (next_permutation(p.begin(), p.end()));
    cout << "P1 brute=" << best << " method=" << assignment(c) << '\n';
    // N1: match 100000 players to 100000 trainers, a player fitting a trainer with capacity at least the player's ability;
    // the sorted greedy gives the most matches, the mask over 100000 trainers has 2^100000 states.
    mt19937 rng(99);
    vector<int> players(100000), trainers(100000);
    for (int& x : players) x = rng() % 1000000;
    for (int& x : trainers) x = rng() % 1000000;
    sort(players.begin(), players.end());
    sort(trainers.begin(), trainers.end());
    int matched = 0;
    for (int t : trainers) if (matched < (int)players.size() && players[matched] <= t) matched++;
    cout << "N1 brute=" << matched << " method=" << (100000 > 22 ? "too-slow" : "ok") << '\n';
}
