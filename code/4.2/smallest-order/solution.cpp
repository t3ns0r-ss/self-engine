/*
Problem: tasks with rules "a before b".
Input: n m, then m lines "a b": task a must be done before task b.
Output: the smallest order (as a sequence of task numbers) in which all tasks can be done, or IMPOSSIBLE.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 4.2.3 and 4.2.5. The smallest order in which every arrow goes from an earlier to a later vertex; an empty list if a
// directed cycle makes every order impossible.
vector<int> smallestOrder(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<int> indegree(n + 1, 0), order;
    for (int u = 1; u <= n; u++)
        for (int w : adj[u]) indegree[w]++;
    priority_queue<int, vector<int>, greater<int>> ready;  // the smallest free vertex comes first
    for (int v = 1; v <= n; v++)
        if (indegree[v] == 0) ready.push(v);
    while (!ready.empty()) {
        int u = ready.top();
        ready.pop();
        order.push_back(u);
        for (int w : adj[u])
            if (--indegree[w] == 0) ready.push(w);
    }
    if ((int)order.size() < n) order.clear();
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
    vector<int> order = smallestOrder(adj);
    if (order.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < n; i++) cout << (i ? " " : "") << order[i];
    cout << "\n";
}
