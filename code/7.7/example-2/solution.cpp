#include <bits/stdc++.h>
using namespace std;

/*
Problem: AtCoder ARC 103 C Tr/ee. A string s of length n (2 <= n <= 10^5) over 0 and 1. Is there a tree with n vertices in which, for every i, removing
some edge leaves a component of size i exactly when s_i = 1? If so, print one.
Input: s.
Output: -1 if there is no such tree; otherwise YES if the program's tree passes its own check (BAD if not).
*/

// snippet:begin
// Necessary: s_1 = 1 (a tree has a leaf), s_n = 0 (no edge removal leaves a component of size n), s_i = s_(n-i) (the two components of an edge
// have sizes i and n - i). These suffice: join the vertex i + 1 to `hold`, and let `hold` become i + 1 whenever s_i = 1.
vector<pair<int, int>> buildTree(const string& s) {  // empty if there is no tree
    int n = s.size();
    bool ok = s[0] == '1' && s[n - 1] == '0';
    for (int i = 1; i < n; i++) ok = ok && s[i - 1] == s[n - i - 1];
    if (!ok) return {};
    vector<pair<int, int>> edges;
    int hold = 1;
    for (int i = 1; i < n; i++) {
        edges.push_back({hold, i + 1});
        if (s[i - 1] == '1') hold = i + 1;
    }
    return edges;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    int n = s.size();
    auto edges = buildTree(s);
    if (edges.empty()) {
        cout << "-1\n";
        return 0;
    }
    // check: the sizes of the components of every edge removal
    vector<vector<int>> g(n + 1);
    for (auto [a, b] : edges) g[a].push_back(b), g[b].push_back(a);
    vector<int> parent(n + 1, 0), order, size(n + 1, 1);
    order.push_back(1);
    for (size_t i = 0; i < order.size(); i++)
        for (int v : g[order[i]])
            if (v != parent[order[i]]) parent[v] = order[i], order.push_back(v);
    string seen(n, '0');
    for (int i = n - 1; i >= 1; i--) {
        int v = order[i];
        size[parent[v]] += size[v];
        seen[size[v] - 1] = '1';
        seen[n - size[v] - 1] = '1';
    }
    cout << ((int)order.size() == n && seen == s ? "YES" : "BAD") << "\n";
}
