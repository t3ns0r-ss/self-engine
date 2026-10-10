/*
Problem: can the vertices be split into two sides with no edge inside a side?
Input: n m, then m lines "a b": an undirected edge between a and b (a != b).
Output: YES or NO.
(The program checks the colouring it finds before printing YES.)
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.1. A colour 0 or 1 for every vertex so that each edge joins different colours; an empty list if that is impossible.
vector<int> twoSides(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<int> colour(n + 1, -1);  // -1 means "not coloured yet"
    for (int s = 1; s <= n; s++) {
        if (colour[s] != -1) continue;  // every component starts from its own vertex
        colour[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int w : adj[u]) {
                if (colour[w] == -1) {
                    colour[w] = 1 - colour[u];
                    q.push(w);
                } else if (colour[w] == colour[u]) {
                    return {};  // an edge inside one colour: an odd cycle
                }
            }
        }
    }
    return colour;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) {
        cin >> e.first >> e.second;
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    vector<int> colour = twoSides(adj);
    if (colour.empty()) {
        cout << "NO\n";
        return 0;
    }
    for (auto [a, b] : edges)
        if (colour[a] == colour[b]) return 2;  // the colouring must be valid
    cout << "YES\n";
}
