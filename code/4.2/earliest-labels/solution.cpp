/*
Problem: courses with rules "a before b" (CSES 1757 style).
Input: n m, then m lines "a b": course a must be completed before course b (a valid schedule exists).
Output: the order of the courses that completes course 1 as early as possible, then course 2 as early as possible, and so on.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.6. The order that puts course 1 as early as possible, then course 2, and so on: build it from the back, always giving
// the last free place to the largest course that no remaining rule puts after it. Empty list if the rules contain a cycle.
vector<int> earliestSmallOrder(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<vector<int>> before(n + 1);  // before[w] lists the courses that must come before w
    vector<int> outDegree(n + 1, 0), order(n);
    for (int u = 1; u <= n; u++)
        for (int w : adj[u]) before[w].push_back(u), outDegree[u]++;
    priority_queue<int> sinks;  // the largest course with nothing left after it
    for (int v = 1; v <= n; v++)
        if (outDegree[v] == 0) sinks.push(v);
    for (int place = n - 1; place >= 0; place--) {
        if (sinks.empty()) return {};
        int v = sinks.top();
        sinks.pop();
        order[place] = v;
        for (int u : before[v])
            if (--outDegree[u] == 0) sinks.push(u);
    }
    return order;
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
    }
    vector<int> order = earliestSmallOrder(adj);
    if (order.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < n; i++) cout << (i ? " " : "") << order[i];
    cout << "\n";
}
