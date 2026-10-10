/*
Problem: CSES 1673, High Score.
Input: n m, then m lines "a b x": a one-way tunnel from a to b adds x to the score (x may be negative; tunnels may be used again and again).
Room n can always be reached from room 1.
Output: the largest score of a walk from room 1 to room n, or -1 if it can be arbitrarily large.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 3. Largest score from 1 to n (every edge {a, b, gain}), or -1 when a positive cycle can be used on the way.
long long highScore(int n, const vector<array<long long, 3>>& edges) {
    const long long NEG = LLONG_MIN / 4;
    vector<vector<int>> fwd(n + 1), back(n + 1);
    for (auto [a, b, x] : edges) fwd[a].push_back(b), back[b].push_back(a);
    auto reach = [&](vector<vector<int>>& g, int s) {  // vertices reachable from s along g
        vector<bool> seen(n + 1, false);
        vector<int> stack = {s};
        seen[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int v : g[u]) if (!seen[v]) seen[v] = true, stack.push_back(v);
        }
        return seen;
    };
    auto fromStart = reach(fwd, 1), toEnd = reach(back, n);
    vector<long long> best(n + 1, NEG);
    best[1] = 0;
    for (int round = 1; round <= n; round++) {
        bool changed = false;
        for (auto [a, b, x] : edges) {
            if (!fromStart[a] || !toEnd[a] || !fromStart[b] || !toEnd[b]) continue;  // only edges on some 1 -> n walk
            if (best[a] > NEG && best[a] + x > best[b]) best[b] = best[a] + x, changed = true;
        }
        if (!changed) break;
        if (round == n) return -1;  // still improving in round n: a positive cycle on a 1 -> n walk
    }
    return best[n];
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> edges(m);
    for (auto& e : edges) cin >> e[0] >> e[1] >> e[2];
    cout << highScore(n, edges) << "\n";
}
