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
// Theorem 4.5.2. For every vertex, the sum of value[] over its subtree (with value = 1 everywhere: the subtree size).
vector<long long> subtreeSums(const Rooted& t, const vector<long long>& value) {
    vector<long long> sum = value;  // sum[v] starts as the value of v alone
    for (int i = t.order.size() - 1; i > 0; i--) {  // backwards: all children of v come after v in the order, so they are added already
        int v = t.order[i];
        sum[t.parent[v]] += sum[v];
    }
    return sum;
}
// snippet:end

int main() {
    {
        vector<vector<int>> adj(6);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(1, 3), edge(3, 4), edge(3, 5);
        auto t = rootAt(adj, 1);
        auto size = subtreeSums(t, vector<long long>(6, 1));
        cout << "tree 1-2, 1-3, 3-4, 3-5 from 1, sizes:";
        for (int v = 1; v <= 5; v++) cout << ' ' << size[v];
        cout << "\n";
        auto sum = subtreeSums(t, {0, 10, 20, 30, 40, 50});
        cout << "values 10 20 30 40 50, subtree sums:";
        for (int v = 1; v <= 5; v++) cout << ' ' << sum[v];
        cout << "\n";
    }
    {
        vector<vector<int>> adj(2);
        auto t = rootAt(adj, 1);
        cout << "one vertex: size " << subtreeSums(t, {0, 1})[1] << "\n";
    }
    // Check against: for each vertex, a separate walk that counts the vertices whose path to the root passes through it.
    mt19937 rng(4502);
    auto randomTree = [](mt19937& rng, int n) {
        vector<int> label(n);
        iota(label.begin(), label.end(), 1);
        shuffle(label.begin(), label.end(), rng);
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int a = label[i], b = label[rng() % i];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        return adj;
    };
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 9 + 1, root = rng() % n + 1;
        auto adj = randomTree(rng, n);
        auto t = rootAt(adj, root);
        vector<long long> value(n + 1);
        for (int v = 1; v <= n; v++) value[v] = (long long)(rng() % 100) - 20;
        auto sum = subtreeSums(t, value);
        for (int v = 1; v <= n; v++) {
            long long expected = 0;
            for (int u = 1; u <= n; u++)
                for (int x = u; x != 0; x = t.parent[x])
                    if (x == v) { expected += value[u]; break; }
            if (sum[v] != expected) return 1;
        }
    }
}
