#include <bits/stdc++.h>
using namespace std;

/*
Problem: a directed graph of n vertices and m edges (up to 10^5 each). Print the topological order that is smallest in the order of the
vertex numbers (a vertex with no unprocessed incoming edge is taken, always the smallest such), or IMPOSSIBLE if the graph has a cycle.
Input: n, m, then the m edges "a b".
Output: the order on one line, or IMPOSSIBLE.
*/


// snippet:begin
// Theorem 7.2.1 (Kahn's algorithm) with a heap, so that the smallest available vertex is taken first. The order is complete exactly
// when there is no directed cycle.
vector<int> smallestTopologicalOrder(const vector<vector<int>>& out, vector<int> indeg) {
    int n = out.size();
    priority_queue<int, vector<int>, greater<int>> ready;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) ready.push(v);
    vector<int> order;
    while (!ready.empty()) {
        int v = ready.top();
        ready.pop();
        order.push_back(v);
        for (int u : out[v])
            if (--indeg[u] == 0) ready.push(u);
    }
    return order;  // shorter than n if there is a cycle
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> out(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a - 1].push_back(b - 1), indeg[b - 1]++;
    }
    vector<int> order = smallestTopologicalOrder(out, indeg);
    if ((int)order.size() < n) return cout << "IMPOSSIBLE\n", 0;
    for (int i = 0; i < n; i++) cout << order[i] + 1 << (i + 1 < n ? " " : "\n");
}
