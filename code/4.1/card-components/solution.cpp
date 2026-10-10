#include <bits/stdc++.h>
using namespace std;

// Method: count the traversals started by the loop of Theorem 4.1.2 (arrows are followed in one direction only).
int countWalks(int n, const vector<pair<int, int>>& arcs) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : arcs) adj[a].push_back(b);
    vector<bool> marked(n + 1, false);
    int walks = 0;
    for (int s = 1; s <= n; s++) {
        if (marked[s]) continue;
        walks++;
        marked[s] = true;
        vector<int> stack = {s};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int w : adj[u])
                if (!marked[w]) {
                    marked[w] = true;
                    stack.push_back(w);
                }
        }
    }
    return walks;
}

// Brute force: the groups are the classes of "u and v reach each other"; reachability by the closure of the arrows.
int countGroups(int n, const vector<pair<int, int>>& arcs) {
    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
    for (int v = 1; v <= n; v++) reach[v][v] = true;
    for (auto [a, b] : arcs) reach[a][b] = true;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;
    int groups = 0;
    for (int v = 1; v <= n; v++) {
        bool first = true;
        for (int u = 1; u < v; u++)
            if (reach[u][v] && reach[v][u]) first = false;
        groups += first;
    }
    return groups;
}

int main() {
    // P1: 6 cities, two-way roads 1-2, 2-3, 1-3, 4-5 (each road is two arrows).
    vector<pair<int, int>> roads = {{1, 2}, {2, 3}, {1, 3}, {4, 5}}, both;
    for (auto [a, b] : roads) {
        both.push_back({a, b});
        both.push_back({b, a});
    }
    cout << "P1 brute=" << countGroups(6, both) << " method=" << countWalks(6, both) << "\n";
    // N1: 4 cities, one-way roads 1->2, 2->1, 2->3, 3->4; groups of cities that can all reach each other.
    vector<pair<int, int>> arrows = {{1, 2}, {2, 1}, {2, 3}, {3, 4}};
    cout << "N1 brute=" << countGroups(4, arrows) << " method=" << countWalks(4, arrows) << "\n";
}
