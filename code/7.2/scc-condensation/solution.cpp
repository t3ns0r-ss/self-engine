#include <bits/stdc++.h>
using namespace std;

/*
Problem: a directed graph of n vertices and m edges (up to 10^5). Print the number of strongly connected components and the number of
different edges between components in the condensation.
Input: n, m, then the m edges "a b".
Output: "components edges".
*/


// snippet:begin
// Theorem 7.2.3: Kosaraju's algorithm without recursion. First pass: the order in which the vertices finish on the graph. Second pass,
// on the reversed graph, from the vertex that finished last: each search finds one component, and the components come out in a
// topological order of the condensation. Returns the number of components; comp[v] is the number of the component of v.
int stronglyConnected(const vector<vector<int>>& out, vector<int>& comp) {
    int n = out.size(), comps = 0;
    vector<vector<int>> in(n);
    for (int v = 0; v < n; v++)
        for (int u : out[v]) in[u].push_back(v);
    vector<int> finish, next(n, 0), stack;
    vector<char> seen(n, 0);
    for (int s = 0; s < n; s++) {
        if (seen[s]) continue;
        seen[s] = 1, stack = {s};
        while (!stack.empty()) {
            int v = stack.back();
            if (next[v] < (int)out[v].size()) {
                int u = out[v][next[v]++];
                if (!seen[u]) seen[u] = 1, stack.push_back(u);
            } else finish.push_back(v), stack.pop_back();
        }
    }
    comp.assign(n, -1);
    for (int i = n - 1; i >= 0; i--) {
        int s = finish[i];
        if (comp[s] >= 0) continue;
        comp[s] = comps, stack = {s};
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            for (int u : in[v])
                if (comp[u] < 0) comp[u] = comps, stack.push_back(u);
        }
        comps++;
    }
    return comps;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> out(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a - 1].push_back(b - 1);
    }
    vector<int> comp;
    int comps = stronglyConnected(out, comp);
    set<pair<int, int>> between;
    for (int v = 0; v < n; v++)
        for (int u : out[v])
            if (comp[u] != comp[v]) between.insert({comp[v], comp[u]});
    cout << comps << " " << between.size() << "\n";
}
