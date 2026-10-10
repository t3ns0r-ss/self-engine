/*
Problem: CSES 1668, Building Teams.
Input: n m, then m lines "a b": pupils a and b are friends (a != b, at most one friendship per pair).
Output: for every pupil the team 1 or 2 so that no two friends share a team, or IMPOSSIBLE.
(This program prints the lexicographically smallest assignment, which any correct judge accepts.)
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 1. The team (1 or 2) of every pupil so that friends are in different teams; an empty list if that is impossible.
vector<int> buildTeams(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<int> team(n + 1, 0);  // 0 means "not placed yet"
    for (int s = 1; s <= n; s++) {
        if (team[s] != 0) continue;
        team[s] = 1;
        vector<int> stack = {s};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int w : adj[u]) {
                if (team[w] == 0) {
                    team[w] = 3 - team[u];  // the other team: 1 becomes 2, 2 becomes 1
                    stack.push_back(w);
                } else if (team[w] == team[u]) {
                    return {};  // two friends in one team
                }
            }
        }
    }
    team.erase(team.begin());
    return team;
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
    vector<int> team = buildTeams(adj);
    if (team.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < n; i++) cout << (i ? " " : "") << team[i];
    cout << "\n";
}
