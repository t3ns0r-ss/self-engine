#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    // all labelled trees through Prufer sequences
    int count = 1;
    for (int i = 0; i < n - 2; i++) count *= n;
    for (int code = 0; code < count; code++) {
        vector<int> prufer(n - 2), degree(n, 1);
        for (int i = 0, c = code; i < n - 2; i++, c /= n) prufer[i] = c % n, degree[prufer[i]]++;
        vector<pair<int, int>> edges;
        set<int> leaves;
        for (int v = 0; v < n; v++)
            if (degree[v] == 1) leaves.insert(v);
        for (int x : prufer) {
            int leaf = *leaves.begin();
            leaves.erase(leaves.begin());
            edges.push_back({leaf, x});
            if (--degree[x] == 1) leaves.insert(x);
        }
        int a = *leaves.begin(), b = *leaves.rbegin();
        edges.push_back({a, b});
        string seen(n, '0');
        for (auto removed : edges) {  // component of one end after removing the edge
            vector<vector<int>> g(n);
            for (auto e : edges)
                if (e != removed) g[e.first].push_back(e.second), g[e.second].push_back(e.first);
            vector<bool> vis(n, false);
            vector<int> st = {removed.first};
            vis[removed.first] = true;
            int size = 0;
            while (!st.empty()) {
                int v = st.back();
                st.pop_back();
                size++;
                for (int u : g[v])
                    if (!vis[u]) vis[u] = true, st.push_back(u);
            }
            seen[size - 1] = '1';
            seen[n - size - 1] = '1';
        }
        if (seen == s) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "-1\n";
}
