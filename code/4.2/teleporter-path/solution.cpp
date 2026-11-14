/*
Problem: use every teleporter exactly once.
Input: n m, then m lines "a b": a one-way teleporter from level a to level b (all pairs different).
Output: the number of levels visited (with repeats) on a route that starts at level 1, ends at level n and uses every
teleporter exactly once, or IMPOSSIBLE. (A real judge wants the route itself; this program prints its length after checking it.)
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.7. A route from level 1 to level n through every teleporter exactly once; empty if there is none.
vector<int> teleporterPath(int n, const vector<pair<int, int>>& teleporters) {
    vector<vector<int>> adj(n + 1);
    vector<int> balance(n + 1, 0);  // teleporters leaving a level minus teleporters entering it
    for (auto [a, b] : teleporters) {
        adj[a].push_back(b);
        balance[a]++;
        balance[b]--;
    }
    for (int v = 1; v <= n; v++)  // the start leaves one more than it enters, the end one fewer
        if (balance[v] != (v == 1 ? 1 : v == n ? -1 : 0)) return {};
    vector<int> next(n + 1, 0), stack = {1}, route;  // next[v]: first teleporter of adj[v] not yet used
    while (!stack.empty()) {
        int v = stack.back();
        if (next[v] == (int)adj[v].size()) {  // no unused teleporter: v is final
            route.push_back(v);
            stack.pop_back();
        } else {
            stack.push_back(adj[v][next[v]++]);
        }
    }
    if (route.size() != teleporters.size() + 1) return {};  // some teleporters cannot be reached from level 1
    reverse(route.begin(), route.end());  // levels were finished from the end of the route backwards
    return route;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> teleporters(m);
    for (auto& [a, b] : teleporters) cin >> a >> b;
    vector<int> route = teleporterPath(n, teleporters);
    if (route.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    // Check the route: it goes from 1 to n and uses every teleporter once.
    multiset<pair<int, int>> left(teleporters.begin(), teleporters.end());
    bool ok = route.front() == 1 && route.back() == n && (int)route.size() == m + 1;
    for (size_t i = 0; ok && i + 1 < route.size(); i++) {
        auto it = left.find({route[i], route[i + 1]});
        if (it == left.end()) ok = false;
        else left.erase(it);
    }
    if (ok) cout << route.size() << "\n";
    else cout << "INVALID\n";
}
