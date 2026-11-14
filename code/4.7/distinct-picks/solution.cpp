/*
Problem: pick distinct numbers.
Input: n, then n lines "a b": item i must take the number a or the number b.
Output: YES when every item can take one of its two numbers so that no number is taken twice, else NO.
*/
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

// snippet:begin
// Theorem 4.7.7 with a chain for "at most one". Item i takes a[i] (variable i is true) or b[i] (false). Can all taken numbers differ?
// For each number, its takers are listed as literals; the chain variable q_j means "one of the first j takers is true".
bool canTakeDistinct(const vector<int>& a, const vector<int>& b) {
    int n = a.size(), vars = n;
    map<int, vector<int>> takers;  // number -> the literals that take it
    for (int i = 1; i <= n; i++) takers[a[i - 1]].push_back(i), takers[b[i - 1]].push_back(-i);
    vector<pair<int, int>> clauses;
    for (auto& [number, lits] : takers) {
        int before = 0;  // q of the previous taker, 0 for the first
        for (int lit : lits) {
            int q = ++vars;
            clauses.push_back({-lit, q});                 // lit true  -> q true
            if (before) clauses.push_back({-before, q});  // q before  -> q true
            if (before) clauses.push_back({-before, -lit});  // q before -> this taker is false
            before = q;
        }
    }
    return !solveTwoSat(vars, clauses).empty();
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    cout << (canTakeDistinct(a, b) ? "YES" : "NO") << "\n";
}
