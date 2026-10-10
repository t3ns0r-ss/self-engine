/*
Problem: LeetCode 802, Find Eventual Safe States.
Input: n, then for each node i = 0 .. n-1 a line "k v_1 ... v_k": the nodes that i has an arrow to.
Output: the safe nodes in increasing order (a node is safe if every path from it ends at a terminal node), on one line;
an empty line if there are none.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 3. The safe nodes in increasing order: take away, again and again, the nodes all of whose arrows lead to nodes already
// taken away. This is Theorem 4.2.3 on the reversed arrows; the nodes that never go are on a cycle or lead into one.
vector<int> safeNodes(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> reverse(n);  // reverse[w] lists the nodes with an arrow to w
    vector<int> outDegree(n), ready, safe;
    for (int u = 0; u < n; u++) {
        outDegree[u] = graph[u].size();
        for (int w : graph[u]) reverse[w].push_back(u);
        if (outDegree[u] == 0) ready.push_back(u);  // terminal nodes
    }
    while (!ready.empty()) {
        int u = ready.back();
        ready.pop_back();
        safe.push_back(u);
        for (int p : reverse[u])
            if (--outDegree[p] == 0) ready.push_back(p);
    }
    sort(safe.begin(), safe.end());
    return safe;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        graph[i].resize(k);
        for (int& v : graph[i]) cin >> v;
    }
    vector<int> safe = safeNodes(graph);
    for (size_t i = 0; i < safe.size(); i++) cout << (i ? " " : "") << safe[i];
    cout << "\n";
}
