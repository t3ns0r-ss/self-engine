#include <bits/stdc++.h>
using namespace std;

using Digraph = vector<vector<int>>;

vector<int> walk(const Digraph& g, int s, vector<bool>& seen) {
    vector<int> done;
    vector<pair<int, int>> stack = {{s, 0}};  // (vertex, how many of its edges were looked at)
    seen[s] = true;
    while (!stack.empty()) {
        auto [v, i] = stack.back();
        if (i == (int)g[v].size()) done.push_back(v), stack.pop_back();
        else {
            stack.back().second++;
            if (!seen[g[v][i]]) seen[g[v][i]] = true, stack.push_back({g[v][i], 0});
        }
    }
    return done;
}
vector<int> stronglyConnected(const Digraph& adj, int& count) {
    int n = adj.size() - 1;
    Digraph rev(n + 1);
    for (int v = 1; v <= n; v++) for (int to : adj[v]) rev[to].push_back(v);
    vector<bool> seen(n + 1, false);
    vector<int> finish, comp(n + 1, 0);
    for (int s = 1; s <= n; s++) if (!seen[s]) for (int v : walk(adj, s, seen)) finish.push_back(v);
    seen.assign(n + 1, false), count = 0;
    for (int i = n - 1; i >= 0; i--) {  // the vertex that finished last first; each walk is one component, numbered 1, 2, ... as found
        if (seen[finish[i]]) continue;
        count++;
        for (int v : walk(rev, finish[i], seen)) comp[v] = count;
    }
    return comp;
}


// Theorem 4.7.7. A literal +x means "x is true" and -x means "x is false". Each clause (a or b) is a pair of literals. Returns a
// satisfying assignment (value[1..n]) or an empty vector when there is none.
vector<bool> solveTwoSat(int n, const vector<pair<int, int>>& clauses) {
    auto node = [&](int lit) { return lit > 0 ? lit : n - lit; };  // x is vertex x, "not x" is vertex n + x
    Digraph adj(2 * n + 1);
    for (auto [a, b] : clauses) {  // (a or b): if a is false then b is true, and if b is false then a is true
        adj[node(-a)].push_back(node(b));
        adj[node(-b)].push_back(node(a));
    }
    int count;
    auto comp = stronglyConnected(adj, count);
    vector<bool> value(n + 1);
    for (int x = 1; x <= n; x++) {
        if (comp[x] == comp[n + x]) return {};  // x and "not x" reach each other
        value[x] = comp[x] > comp[n + x];       // x is true when its group comes later
    }
    return value;
}

// All assignments by brute force: how many satisfy every clause (a clause is a list of literals, one of which must hold)?
vector<int> bruteAssignments(int n, const vector<vector<int>>& clauses, int& fewestTrue) {
    vector<int> good;
    fewestTrue = n + 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        auto holds = [&](int lit) { return lit > 0 ? (mask >> (lit - 1) & 1) == 1 : (mask >> (-lit - 1) & 1) == 0; };
        bool ok = true;
        for (auto& clause : clauses) {
            bool any = false;
            for (int lit : clause) any = any || holds(lit);
            ok = ok && any;
        }
        if (ok) good.push_back(mask), fewestTrue = min(fewestTrue, __builtin_popcount(mask));
    }
    return good;
}

int main() {
    int fewest;
    {
        vector<vector<int>> clauses = {{1, 2}, {-1, 3}, {-2, -3}};
        int brute = bruteAssignments(3, clauses, fewest).empty() ? 0 : 1;
        int method = solveTwoSat(3, {{1, 2}, {-1, 3}, {-2, -3}}).empty() ? 0 : 1;
        cout << "P1 brute=" << brute << " method=" << method << "\n";
    }
    {
        vector<vector<int>> clauses = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
        int brute = bruteAssignments(2, clauses, fewest).empty() ? 0 : 1;
        int method = solveTwoSat(2, {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}}).empty() ? 0 : 1;
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    {
        // A guest with three wishes: the wrong method turns the triple into its three pairs, which asks for two true wishes.
        vector<vector<int>> clauses = {{1, 2, 3}, {-1, -2}, {-1, -3}, {-2, -3}};
        int brute = bruteAssignments(3, clauses, fewest).empty() ? 0 : 1;
        int method = solveTwoSat(3, {{1, 2}, {1, 3}, {2, 3}, {-1, -2}, {-1, -3}, {-2, -3}}).empty() ? 0 : 1;
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
    {
        // Fewest toppings: the assignment of the theorem is some valid pizza, not the smallest.
        vector<vector<int>> clauses = {{1, 2}, {1, 3}, {1, 4}};
        bruteAssignments(4, clauses, fewest);
        auto value = solveTwoSat(4, {{1, 2}, {1, 3}, {1, 4}});
        int method = 0;
        for (int x = 1; x <= 4; x++) method += value[x];
        cout << "N2 brute=" << fewest << " method=" << method << "\n";
    }
}
