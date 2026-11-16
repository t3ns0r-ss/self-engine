#include <bits/stdc++.h>
using namespace std;

// Brute force: dp[i][mask] = the most pairs among left items i.. when the right items in mask are already used.
int L, R;
vector<int> adj[8];
int memo[9][1 << 8];
int best(int i, int mask) {
    if (i == L) return 0;
    int& r = memo[i][mask];
    if (r >= 0) return r;
    r = best(i + 1, mask);  // left item i stays alone
    for (int v : adj[i])
        if (!(mask >> v & 1)) r = max(r, 1 + best(i + 1, mask | 1 << v));
    return r;
}
int main() {
    int m;
    cin >> L >> R >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
    }
    memset(memo, -1, sizeof memo);
    cout << best(0, 0) << "\n";
}
