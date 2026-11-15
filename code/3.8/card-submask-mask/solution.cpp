#include <bits/stdc++.h>
using namespace std;

long long bestPartition(const vector<long long>& w, long long cap) {
    int n = w.size(), full = (1 << n) - 1;
    vector<long long> sum(1 << n, 0), dp(1 << n, -1);
    for (int mask = 1; mask <= full; mask++) { int low = __builtin_ctz(mask); sum[mask] = sum[mask ^ 1 << low] + w[low]; }
    dp[0] = 0;
    for (int mask = 1; mask <= full; mask++) {
        int low = mask & -mask;
        for (int s = mask; s > 0; s = (s - 1) & mask) {
            if (!(s & low) || sum[s] > cap) continue;
            dp[mask] = max(dp[mask], dp[mask ^ s] + sum[s] * sum[s]);
        }
    }
    return dp[full];
}
long long brute(const vector<long long>& w, long long cap, int i, vector<long long>& groups) {
    if (i == (int)w.size()) { long long s = 0; for (long long g : groups) s += g * g; return s; }
    long long best = -1;
    for (size_t g = 0; g < groups.size(); g++)
        if (groups[g] + w[i] <= cap) { groups[g] += w[i]; best = max(best, brute(w, cap, i + 1, groups)); groups[g] -= w[i]; }
    groups.push_back(w[i]);
    best = max(best, brute(w, cap, i + 1, groups));
    groups.pop_back();
    return best;
}
int main() {
    // P1: weights 3 2 2 with capacity 5, a group scoring the square of its total. P2: weights 1 2 3 4 with capacity 5.
    vector<long long> a = {3, 2, 2}, b = {1, 2, 3, 4}, g1, g2;
    cout << "P1 brute=" << brute(a, 5, 0, g1) << " method=" << bestPartition(a, 5) << '\n';
    cout << "P2 brute=" << brute(b, 5, 0, g2) << " method=" << bestPartition(b, 5) << '\n';
    // N1: the number of subsets of 20 numbers whose OR is the largest possible. Each subset is judged alone: 2^20 masks; 3^20 pairs would be too slow.
    mt19937 rng(3);
    vector<int> v(20);
    for (int& x : v) x = rng() % 1024;
    vector<int> orOf(1 << 20, 0);
    int best = 0;
    for (int mask = 1; mask < (1 << 20); mask++) { int low = __builtin_ctz(mask); orOf[mask] = orOf[mask & (mask - 1)] | v[low]; best = max(best, orOf[mask]); }
    long long count = 0;
    for (int mask = 1; mask < (1 << 20); mask++) count += orOf[mask] == best;
    long long pairs = 1;
    for (int i = 0; i < 20; i++) pairs *= 3;
    cout << "N1 brute=" << count << " method=" << (pairs > 100000000LL ? "too-slow" : "ok") << '\n';
}
