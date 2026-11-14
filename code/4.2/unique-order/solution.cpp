/*
Problem: a hidden permutation A of 1..n, and m facts "A_x < A_y".
Input: n m, then m lines "x y".
Output: "Yes" and then A_1 ... A_n if the facts leave exactly one permutation, otherwise "No".
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.8. The one order of the vertices in which every edge goes forward; empty if there is none or more than one.
vector<int> onlyOrder(int n, const vector<pair<int, int>>& before) {
    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0), ready, order;
    for (auto [a, b] : before) {
        adj[a].push_back(b);
        indegree[b]++;
    }
    for (int v = 1; v <= n; v++)
        if (indegree[v] == 0) ready.push_back(v);
    while (!ready.empty()) {
        if (ready.size() > 1) return {};  // two free vertices can be swapped, so the order is not unique
        int u = ready.back();
        ready.pop_back();
        order.push_back(u);
        for (int w : adj[u])
            if (--indegree[w] == 0) ready.push_back(w);
    }
    if ((int)order.size() < n) order.clear();  // a directed cycle blocks every order
    return order;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> before(m);
    for (auto& [x, y] : before) cin >> x >> y;
    vector<int> order = onlyOrder(n, before);
    if (order.empty()) {
        cout << "No\n";
        return 0;
    }
    vector<int> value(n + 1);
    for (int i = 0; i < n; i++) value[order[i]] = i + 1;
    cout << "Yes\n";
    for (int v = 1; v <= n; v++) cout << value[v] << (v < n ? " " : "\n");
}
