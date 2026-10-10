/*
Problem: who is above whom.
Input: n, then n - 1 numbers p_2..p_n (the parent of vertex i is p_i, and p_i < i; vertex 1 is the root), then q, then q lines "u v".
Output: for each question YES if u is an ancestor of v (u = v counts), otherwise NO.
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
// Theorem 4.5.3. Ancestor questions by comparing the ranges of the visit order.
vector<bool> ancestorAnswers(const vector<vector<int>>& adj, const vector<pair<int, int>>& questions) {
    int n = adj.size() - 1;
    auto t = rootAt(adj, 1);
    vector<int> tin(n + 1), size(n + 1, 1);
    for (int i = 0; i < n; i++) tin[t.order[i]] = i;
    for (int i = n - 1; i > 0; i--) size[t.parent[t.order[i]]] += size[t.order[i]];
    vector<bool> answer;
    for (auto [u, v] : questions) answer.push_back(tin[u] <= tin[v] && tin[v] < tin[u] + size[u]);  // v lies in the block of u
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
    auto answer = ancestorAnswers(adj, questions);
    for (bool a : answer) cout << (a ? "YES" : "NO") << "\n";
}
