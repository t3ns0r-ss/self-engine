/*
Problem: planets with teleporters (CSES 1750 style).
Input: n q, then t_1..t_n (the teleporter of planet i leads to planet t_i, possibly itself), then q lines "x k".
Output: for each query, the planet reached from x after using k teleporters (0 <= k <= 10^9).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.6.1 on pointers: up[j][v] is the planet reached from v after 2^j teleporters. next[v] is the teleporter of v; planets are 1..n.
vector<int> afterKSteps(const vector<int>& next, const vector<pair<int, long long>>& queries) {
    int n = next.size() - 1, levels = 31;  // 2^31 > 10^9
    vector<vector<int>> up(levels, next);
    for (int j = 1; j < levels; j++)
        for (int v = 1; v <= n; v++) up[j][v] = up[j - 1][up[j - 1][v]];  // two jumps of 2^(j-1)
    vector<int> answer;
    for (auto [x, k] : queries) {
        for (int j = 0; j < levels; j++)
            if (k >> j & 1) x = up[j][x];  // the order of the jumps does not matter
        answer.push_back(x);
    }
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> next(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> next[i];
    vector<pair<int, long long>> queries(q);
    for (auto& x : queries) cin >> x.first >> x.second;
    for (int a : afterKSteps(next, queries)) cout << a << "\n";
}
