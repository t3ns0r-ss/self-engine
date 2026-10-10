#include <bits/stdc++.h>
using namespace std;

// Method: depth-first search with the three vertex states (Theorem 4.2.4); returns the cycle found, sorted, as a string of vertices.
string cycleByStates(int n, const vector<pair<int, int>>& arrows) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : arrows) adj[a].push_back(b);
    vector<int> state(n + 1, 0), nextIndex(n + 1, 0), stack;
    for (int s = 1; s <= n; s++) {
        if (state[s] != 0) continue;
        stack = {s};
        state[s] = 1;
        while (!stack.empty()) {
            int u = stack.back();
            if (nextIndex[u] == (int)adj[u].size()) {
                state[u] = 2;
                stack.pop_back();
                continue;
            }
            int w = adj[u][nextIndex[u]++];
            if (state[w] == 1) {
                vector<int> cycle(find(stack.begin(), stack.end(), w), stack.end());
                sort(cycle.begin(), cycle.end());
                string text;
                for (int v : cycle) text += to_string(v);
                return text;
            }
            if (state[w] == 0) {
                state[w] = 1;
                stack.push_back(w);
            }
        }
    }
    return "none";
}

// Brute force: the vertices that lie on a directed cycle are those that can reach themselves (closure over the arrows).
string onCycles(int n, const vector<pair<int, int>>& arrows) {
    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
    for (auto [a, b] : arrows) reach[a][b] = true;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;
    string text;
    for (int v = 1; v <= n; v++)
        if (reach[v][v]) text += to_string(v);
    return text.empty() ? "none" : text;
}

int main() {
    // P1: five towns, one-way roads 1>2, 2>3, 3>4, 4>2, 5>4; the towns that lie on the cycle.
    vector<pair<int, int>> roads = {{1, 2}, {2, 3}, {3, 4}, {4, 2}, {5, 4}};
    cout << "P1 brute=" << onCycles(5, roads) << " method=" << cycleByStates(5, roads) << "\n";
    // P2: renames 1>2, 2>3, 3>1, 4>1: which names are on a cycle of renames?
    vector<pair<int, int>> renames = {{1, 2}, {2, 3}, {3, 1}, {4, 1}};
    cout << "P2 brute=" << onCycles(4, renames) << " method=" << cycleByStates(4, renames) << "\n";
    // N1: one two-way road 1-2, read as the two arrows 1>2 and 2>1. A single road is not a cycle of an undirected graph.
    vector<pair<int, int>> oneRoad = {{1, 2}, {2, 1}};
    int edges = 1, vertices = 2, components = 1;  // brute force: an undirected graph is a forest when m = n - c
    string brute = edges > vertices - components ? "yes" : "no";
    string method = cycleByStates(2, oneRoad) == "none" ? "no" : "yes";
    cout << "N1 brute=" << brute << " method=" << method << "\n";
}
