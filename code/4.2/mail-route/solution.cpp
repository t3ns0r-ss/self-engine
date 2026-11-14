/*
Problem: a mail route through two-way streets.
Input: n m, then m lines "a b": a street between crossings a and b. The post office is at crossing 1.
Output: the length (number of crossings, counted with repeats) of a route that starts and ends at crossing 1 and uses every
street exactly once, or IMPOSSIBLE. (A real judge wants the route itself; this program prints its length after checking it.)
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.7. A route from crossing 1 through every street exactly once, back to crossing 1; empty if there is none.
vector<int> mailRoute(int n, const vector<pair<int, int>>& streets) {
    int m = streets.size();
    vector<vector<pair<int, int>>> adj(n + 1);  // adj[v] holds (other end, street number)
    for (int i = 0; i < m; i++) {
        adj[streets[i].first].push_back({streets[i].second, i});
        adj[streets[i].second].push_back({streets[i].first, i});
    }
    for (int v = 1; v <= n; v++)
        if (adj[v].size() % 2 == 1) return {};  // an odd degree rules out a closed route
    vector<bool> used(m, false);
    vector<int> next(n + 1, 0), stack = {1}, route;
    while (!stack.empty()) {
        int v = stack.back();
        while (next[v] < (int)adj[v].size() && used[adj[v][next[v]].second]) next[v]++;
        if (next[v] == (int)adj[v].size()) {  // no unused street: v is final
            route.push_back(v);
            stack.pop_back();
        } else {
            used[adj[v][next[v]].second] = true;
            stack.push_back(adj[v][next[v]].first);
        }
    }
    if ((int)route.size() != m + 1) return {};  // some streets cannot be reached from crossing 1
    return route;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> streets(m);
    for (auto& [a, b] : streets) cin >> a >> b;
    vector<int> route = mailRoute(n, streets);
    if (route.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    // Check the route: it starts and ends at 1 and uses every street once.
    multiset<pair<int, int>> left;
    for (auto [a, b] : streets) left.insert({min(a, b), max(a, b)});
    bool ok = route.front() == 1 && route.back() == 1 && (int)route.size() == m + 1;
    for (size_t i = 0; ok && i + 1 < route.size(); i++) {
        auto it = left.find({min(route[i], route[i + 1]), max(route[i], route[i + 1])});
        if (it == left.end()) ok = false;
        else left.erase(it);
    }
    if (ok) cout << route.size() << "\n";
    else cout << "INVALID\n";
}
