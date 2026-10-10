#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.4. A directed cycle as a list of vertices (each has an arrow to the next, the last to the first), or an empty list if
// there is none. State of a vertex: 0 not entered, 1 on the stack, 2 finished.
vector<int> findDirectedCycle(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<int> state(n + 1, 0), nextIndex(n + 1, 0), stack;
    for (int s = 1; s <= n; s++) {
        if (state[s] != 0) continue;
        stack = {s};
        state[s] = 1;
        while (!stack.empty()) {
            int u = stack.back();
            if (nextIndex[u] == (int)adj[u].size()) {  // all arrows of u have been tried
                state[u] = 2;
                stack.pop_back();
                continue;
            }
            int w = adj[u][nextIndex[u]++];
            if (state[w] == 1) return vector<int>(find(stack.begin(), stack.end(), w), stack.end());  // w ... u is a cycle
            if (state[w] == 0) {
                state[w] = 1;
                stack.push_back(w);
            }
        }
    }
    return {};
}
// snippet:end

void show(int n, vector<pair<int, int>> arrows) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : arrows) adj[a].push_back(b);
    vector<int> cycle = findDirectedCycle(adj);
    if (cycle.empty()) {
        cout << "no cycle\n";
        return;
    }
    cout << "cycle:";
    for (int v : cycle) cout << ' ' << v;
    cout << "\n";
}

int main() {
    cout << "arrows 1>2 2>3 3>1: ";
    show(3, {{1, 2}, {2, 3}, {3, 1}});
    cout << "arrows 1>2 1>3 2>3: ";
    show(3, {{1, 2}, {1, 3}, {2, 3}});
    cout << "arrows 1>2 2>3 3>2 3>4: ";
    show(4, {{1, 2}, {2, 3}, {3, 2}, {3, 4}});
    // Check against "some vertex reaches itself" (closure) on every directed graph with 4 vertices, and check the cycle returned.
    int n = 4;
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= n; b++)
            if (a != b) pairs.push_back({a, b});
    for (int mask = 0; mask < (1 << pairs.size()); mask++) {
        vector<vector<int>> adj(n + 1);
        bool arrow[5][5] = {}, reach[5][5] = {};
        for (size_t i = 0; i < pairs.size(); i++)
            if (mask >> i & 1) {
                adj[pairs[i].first].push_back(pairs[i].second);
                arrow[pairs[i].first][pairs[i].second] = reach[pairs[i].first][pairs[i].second] = true;
            }
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (reach[i][k] && reach[k][j]) reach[i][j] = true;
        bool bruteCycle = false;
        for (int v = 1; v <= n; v++)
            if (reach[v][v]) bruteCycle = true;
        vector<int> cycle = findDirectedCycle(adj);
        if (cycle.empty() == bruteCycle) return 1;
        if (!cycle.empty()) {
            set<int> distinct(cycle.begin(), cycle.end());
            if (distinct.size() != cycle.size()) return 1;
            for (size_t i = 0; i < cycle.size(); i++)
                if (!arrow[cycle[i]][cycle[(i + 1) % cycle.size()]]) return 1;
        }
    }
}
