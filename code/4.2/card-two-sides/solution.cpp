#include <bits/stdc++.h>
using namespace std;

// Method: the walk of Theorem 4.2.1 (colour each vertex opposite to its parent; a conflict means impossible).
bool twoColourable(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : edges) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> colour(n + 1, -1);
    for (int s = 1; s <= n; s++) {
        if (colour[s] != -1) continue;
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
                    return false;
                }
            }
        }
    }
    return true;
}

// Brute force: try every assignment of `teams` teams to the n people.
bool someSplit(int n, int teams, const vector<pair<int, int>>& edges) {
    int total = 1;
    for (int i = 0; i < n; i++) total *= teams;
    for (int code = 0; code < total; code++) {
        vector<int> team(n + 1);
        int x = code;
        for (int v = 1; v <= n; v++) {
            team[v] = x % teams;
            x /= teams;
        }
        bool ok = true;
        for (auto [a, b] : edges)
            if (team[a] == team[b]) ok = false;
        if (ok) return true;
    }
    return false;
}

const char* word(bool yes) { return yes ? "yes" : "no"; }

int main() {
    // P1: six pupils; pairs that must be in different teams: 1-2, 2-3, 3-4, 4-1, 5-6. Can they form two teams?
    vector<pair<int, int>> enemies = {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {5, 6}};
    cout << "P1 brute=" << word(someSplit(6, 2, enemies)) << " method=" << word(twoColourable(6, enemies)) << "\n";
    // N1: pairs 1-2, 2-3, 1-3 (a triangle). Can THREE teams be formed? The method above only knows two sides.
    vector<pair<int, int>> triangle = {{1, 2}, {2, 3}, {1, 3}};
    cout << "N1 brute=" << word(someSplit(3, 3, triangle)) << " method=" << word(twoColourable(3, triangle)) << "\n";
}
