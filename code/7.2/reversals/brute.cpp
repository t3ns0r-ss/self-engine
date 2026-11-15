#include <bits/stdc++.h>
using namespace std;

// For every vertex v: a search from v that counts the edges met against their direction.
int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> adj(n);  // (neighbour, 1 if the edge points away from this vertex)
    for (int i = 0; i + 1 < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back({v, 1}), adj[v].push_back({u, 0});
    }
    for (int s = 0; s < n; s++) {
        int count = 0;
        vector<int> seen(n, 0), stack = {s};
        seen[s] = 1;
        while (!stack.empty()) {
            int x = stack.back();
            stack.pop_back();
            for (auto [y, away] : adj[x])
                if (!seen[y]) seen[y] = 1, count += !away, stack.push_back(y);
        }
        cout << count << (s + 1 < n ? " " : "\n");
    }
}
