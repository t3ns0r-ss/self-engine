/*
Problem: fewest edges from s to t.
Input: n m s t, then m lines "a b": an undirected edge between a and b.
Output: the least number of edges on a path from s to t, or -1 if there is none.
(The program builds the route itself, checks it, and prints only its length.)
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.3. A route from s to t with the fewest edges, as the list of its vertices (empty if t cannot be reached).
vector<int> fewestRoute(const vector<vector<int>>& adj, int s, int t) {
    vector<int> parent(adj.size(), 0);  // 0 means "not reached yet"
    queue<int> q;
    parent[s] = s;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int w : adj[u]) {
            if (parent[w] == 0) {
                parent[w] = u;  // w was reached from u
                q.push(w);
            }
        }
    }
    if (parent[t] == 0) return {};
    vector<int> route;
    for (int v = t; v != s; v = parent[v]) route.push_back(v);
    route.push_back(s);
    reverse(route.begin(), route.end());
    return route;
}
// snippet:end

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> route = fewestRoute(adj, s, t);
    if (route.empty()) {
        cout << -1 << "\n";
        return 0;
    }
    // Check the route: it starts at s, ends at t, and every step is an edge.
    if (route.front() != s || route.back() != t) return 2;
    for (size_t i = 1; i < route.size(); i++)
        if (find(adj[route[i - 1]].begin(), adj[route[i - 1]].end(), route[i]) == adj[route[i - 1]].end()) return 2;
    cout << route.size() - 1 << "\n";
}
