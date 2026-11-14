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

// snippet:begin
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
// snippet:end

// Test helper: is the assignment good for every clause?
bool satisfies(const vector<bool>& value, const vector<pair<int, int>>& clauses) {
    auto holds = [&](int lit) { return lit > 0 ? value[lit] : !value[-lit]; };
    for (auto [a, b] : clauses)
        if (!holds(a) && !holds(b)) return false;
    return true;
}
// Test helper: tries all 2^n assignments.
bool satisfiable(int n, const vector<pair<int, int>>& clauses) {
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<bool> value(n + 1);
        for (int x = 1; x <= n; x++) value[x] = mask >> (x - 1) & 1;
        if (satisfies(value, clauses)) return true;
    }
    return false;
}
void show(const char* text, int n, const vector<pair<int, int>>& clauses) {
    auto value = solveTwoSat(n, clauses);
    cout << text << ":";
    if (value.empty()) cout << " impossible";
    else
        for (int x = 1; x <= n; x++) cout << " x" << x << "=" << (value[x] ? 1 : 0);
    cout << "\n";
}

int main() {
    show("(x1 or x2), (x1 or not x2), (not x1 or x2), (not x1 or not x2)", 2, {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}});
    show("(x1 or x1), (not x1 or x2), (not x2 or not x3)", 3, {{1, 1}, {-1, 2}, {-2, -3}});
    show("(x1 or x2), (not x1 or x2)", 2, {{1, 2}, {-1, 2}});
    // Exhaustive: every set of clauses over 2 variables (10 possible clauses), and many random ones over 3 to 6 variables.
    for (int n = 2; n <= 3; n++) {
        vector<pair<int, int>> all;
        for (int a = -n; a <= n; a++)
            for (int b = a; b <= n; b++)
                if (a != 0 && b != 0) all.push_back({a, b});
        int limit = n == 2 ? 1 << all.size() : 200000;
        mt19937 pick(4707);
        for (int code = 0; code < limit; code++) {
            vector<pair<int, int>> clauses;
            unsigned bits = n == 2 ? code : pick();
            for (int i = 0; i < (int)all.size(); i++)
                if (bits >> i & 1) clauses.push_back(all[i]);
            auto value = solveTwoSat(n, clauses);
            if (value.empty() == satisfiable(n, clauses)) return 1;
            if (!value.empty() && !satisfies(value, clauses)) return 1;
        }
    }
    mt19937 rng(4707);
    for (int trial = 0; trial < 30000; trial++) {
        int n = rng() % 6 + 1, m = rng() % 12;
        vector<pair<int, int>> clauses;
        for (int i = 0; i < m; i++) {
            int a = rng() % n + 1, b = rng() % n + 1;
            clauses.push_back({rng() % 2 ? a : -a, rng() % 2 ? b : -b});
        }
        auto value = solveTwoSat(n, clauses);
        if (value.empty() == satisfiable(n, clauses)) return 1;
        if (!value.empty() && !satisfies(value, clauses)) return 1;
    }
}
