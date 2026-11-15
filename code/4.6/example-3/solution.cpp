/*
Problem: AtCoder ABC 202 E, Count Descendants.
Input: N, then P_2..P_N (the parent of vertex i is P_i < i; vertex 1 is the root), then Q, then Q lines "U D".
Output: for each question, the number of vertices in the subtree of U (U included) that have depth exactly D.
*/
#include <bits/stdc++.h>
using namespace std;

struct Rooted {
    vector<int> order, parent, depth;
};
Rooted rootAt(const vector<vector<int>>& adj, int root) {
    int n = adj.size() - 1;
    Rooted t{{}, vector<int>(n + 1, 0), vector<int>(n + 1, 0)};
    vector<int> stack = {root};
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        t.order.push_back(u);
        for (int v : adj[u])
            if (v != t.parent[u]) {  // in a tree the only visited neighbour of u is its parent
                t.parent[v] = u;
                t.depth[v] = t.depth[u] + 1;
                stack.push_back(v);
            }
    }
    return t;
}

// snippet:begin
// Example 3. The subtree of u is the block tin[u] .. tin[u] + size[u] - 1 of the visit order. For every depth keep the positions of its
// vertices in increasing order; the answer is the number of positions of depth d inside the block, by two binary searches.
vector<int> countDescendants(const vector<vector<int>>& adj, const vector<pair<int, int>>& questions) {
    int n = adj.size() - 1;
    auto t = rootAt(adj, 1);
    vector<int> tin(n + 1), size(n + 1, 1);
    for (int i = 0; i < n; i++) tin[t.order[i]] = i;
    for (int i = n - 1; i > 0; i--) size[t.parent[t.order[i]]] += size[t.order[i]];
    vector<vector<int>> atDepth(n);  // atDepth[d]: positions of the vertices of depth d, increasing because we go through the order
    for (int i = 0; i < n; i++) atDepth[t.depth[t.order[i]]].push_back(i);
    vector<int> answer;
    for (auto [u, d] : questions) {
        if (d >= n) { answer.push_back(0); continue; }
        auto& list = atDepth[d];
        answer.push_back(upper_bound(list.begin(), list.end(), tin[u] + size[u] - 1) - lower_bound(list.begin(), list.end(), tin[u]));
    }
    return answer;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    int q;
    cin >> q;
    vector<pair<int, int>> questions(q);
    for (auto& x : questions) cin >> x.first >> x.second;
    for (int a : countDescendants(adj, questions)) cout << a << "\n";
}
