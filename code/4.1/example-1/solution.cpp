/*
Problem: CSES 1666, Building Roads.
Input: n m, then m lines "a b": a road between cities a and b (no repeated roads, a != b).
Output: k, the fewest new roads that make every city reachable from every other, then k lines "a b" with the new roads
(this program joins the first city of each group to the first city of the previous group; any valid answer is accepted by the judge).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 1. The new roads: the first city of every group is joined to the first city of the group before it.
vector<pair<int, int>> newRoads(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<bool> marked(n + 1, false);
    vector<pair<int, int>> roads;
    int previous = 0;  // first city of the previous group (0: this is the first group)
    for (int s = 1; s <= n; s++) {
        if (marked[s]) continue;
        if (previous != 0) roads.push_back({previous, s});
        previous = s;
        vector<int> stack = {s};  // walk over the whole group of s
        marked[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int w : adj[u]) {
                if (!marked[w]) {
                    marked[w] = true;
                    stack.push_back(w);
                }
            }
        }
    }
    return roads;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    auto roads = newRoads(adj);
    cout << roads.size() << "\n";
    for (auto [a, b] : roads) cout << a << " " << b << "\n";
}
