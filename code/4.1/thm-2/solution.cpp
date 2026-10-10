#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.2. Give every vertex the number of its component (1, 2, 3, ...) and return how many components there are.
int labelComponents(const vector<vector<int>>& adj, vector<int>& comp) {
    int n = adj.size() - 1, count = 0;
    comp.assign(n + 1, 0);  // 0 means "not visited yet"
    for (int s = 1; s <= n; s++) {
        if (comp[s] != 0) continue;
        count++;  // s starts a component that no earlier traversal reached
        comp[s] = count;
        vector<int> stack = {s};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int w : adj[u]) {
                if (comp[w] == 0) {
                    comp[w] = count;
                    stack.push_back(w);
                }
            }
        }
    }
    return count;
}
// snippet:end

int main() {
    auto run = [&](int n, vector<pair<int, int>> edges) {
        vector<vector<int>> adj(n + 1);
        for (auto [a, b] : edges) {
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        vector<int> comp;
        int count = labelComponents(adj, comp);
        cout << "components: " << count << ", labels";
        for (int v = 1; v <= n; v++) cout << ' ' << comp[v];
        cout << "\n";
    };
    cout << "n=6, edges 1-2 2-3 1-3 4-5: ";
    run(6, {{1, 2}, {2, 3}, {1, 3}, {4, 5}});
    cout << "n=4, no edges: ";
    run(4, {});
    cout << "n=5, edges 1-2 2-3 3-4 4-5: ";
    run(5, {{1, 2}, {2, 3}, {3, 4}, {4, 5}});
    // Check every undirected graph on 5 vertices (2^10): same label exactly when connected; labels are 1..count in order of first vertex.
    int n = 5;
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; a++)
        for (int b = a + 1; b <= n; b++) pairs.push_back({a, b});
    for (int mask = 0; mask < (1 << pairs.size()); mask++) {
        vector<vector<int>> adj(n + 1);
        bool closure[6][6] = {};
        for (int v = 1; v <= n; v++) closure[v][v] = true;
        for (size_t i = 0; i < pairs.size(); i++) {
            if (!(mask >> i & 1)) continue;
            auto [a, b] = pairs[i];
            adj[a].push_back(b);
            adj[b].push_back(a);
            closure[a][b] = closure[b][a] = true;
        }
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (closure[i][k] && closure[k][j]) closure[i][j] = true;
        vector<int> comp;
        int count = labelComponents(adj, comp);
        int expected = 0;
        for (int v = 1; v <= n; v++) {
            bool firstOfClass = true;
            for (int u = 1; u < v; u++)
                if (closure[u][v]) firstOfClass = false;
            expected += firstOfClass;
            for (int u = 1; u <= n; u++)
                if ((comp[u] == comp[v]) != closure[u][v]) return 1;
        }
        if (count != expected) return 1;
    }
}
