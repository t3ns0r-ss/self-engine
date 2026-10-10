#include <bits/stdc++.h>
using namespace std;

// Method: Kahn's process with a min-heap (Theorems 4.2.3 and 4.2.5); returns the order, or an empty list if a cycle blocks it.
vector<int> heapOrder(int n, const vector<pair<int, int>>& before) {
    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0), order;
    for (auto [a, b] : before) {
        adj[a].push_back(b);
        indegree[b]++;
    }
    priority_queue<int, vector<int>, greater<int>> ready;
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

string joined(const vector<int>& order) {
    string s;
    for (int v : order) s += to_string(v);
    return s.empty() ? "none" : s;
}

// Brute force: every permutation of the items; keep those in which each pair (a, b) has a before b. Permutations come in
// increasing order, so the first one found is the smallest.
vector<vector<int>> validOrders(int n, const vector<pair<int, int>>& before, bool immediately) {
    vector<vector<int>> found;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    do {
        vector<int> position(n + 1);
        for (int i = 0; i < n; i++) position[perm[i]] = i;
        bool ok = true;
        for (auto [a, b] : before) {
            if (immediately ? position[b] != position[a] + 1 : position[a] > position[b]) ok = false;
        }
        if (ok) found.push_back(perm);
    } while (next_permutation(perm.begin(), perm.end()));
    return found;
}

int main() {
    // P1: five items; rules 4 before 2, 5 before 1, 3 before 1; the smallest valid order.
    vector<pair<int, int>> rules = {{4, 2}, {5, 1}, {3, 1}};
    auto all = validOrders(5, rules, false);
    cout << "P1 brute=" << joined(all.empty() ? vector<int>() : all[0]) << " method=" << joined(heapOrder(5, rules)) << "\n";
    // P2: four tasks; rules 1 before 2, 2 before 3, 3 before 1, 3 before 4: is there a valid order?
    vector<pair<int, int>> circular = {{1, 2}, {2, 3}, {3, 1}, {3, 4}};
    cout << "P2 brute=" << (validOrders(4, circular, false).empty() ? "no" : "yes") << " method=" << (heapOrder(4, circular).empty() ? "no" : "yes") << "\n";
    // N1: three items; the rule is "1 stands immediately before 3". The arrow model only says "1 before 3": it allows more orders.
    vector<pair<int, int>> adjacent = {{1, 3}};
    cout << "N1 brute=" << validOrders(3, adjacent, true).size() << " method=" << validOrders(3, adjacent, false).size() << "\n";
}
