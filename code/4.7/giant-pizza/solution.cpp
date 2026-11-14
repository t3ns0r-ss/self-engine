/*
Problem: giant pizza (CSES 1684 style).
Input: n m, then n lines "s x t y": a guest wishes that topping x is good (s = +) or bad (s = -), and the same for topping y.
Output: POSSIBLE when some choice of toppings gives every guest at least one of the two wishes, else IMPOSSIBLE.
(The real problem prints the pizza; the program checks the pizza itself and prints only the verdict, so that the brute force can compare.)
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
// Theorem 4.7.7 on the pizza problem. A wish is +x (topping x is good) or -x (topping x is bad); each guest gives two wishes and at
// least one must come true. Returns one symbol per topping ('+' included, '-' left out) or "IMPOSSIBLE".
string choosePizza(int m, const vector<pair<int, int>>& guests) {
    auto value = solveTwoSat(m, guests);
    if (value.empty()) return "IMPOSSIBLE";
    string pizza;
    for (int x = 1; x <= m; x++) pizza += value[x] ? '+' : '-';
    return pizza;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> guests(n);
    for (auto& [a, b] : guests) {
        char sign1, sign2;
        int x, y;
        cin >> sign1 >> x >> sign2 >> y;
        a = sign1 == '+' ? x : -x;
        b = sign2 == '+' ? y : -y;
    }
    string pizza = choosePizza(m, guests);
    if (pizza == "IMPOSSIBLE") {
        cout << pizza << "\n";
        return 0;
    }
    // Check the answer with the wishes themselves: every guest must get at least one.
    for (auto [a, b] : guests) {
        bool first = (a > 0) == (pizza[abs(a) - 1] == '+'), second = (b > 0) == (pizza[abs(b) - 1] == '+');
        if (!first && !second) return 1;
    }
    cout << "POSSIBLE\n";
}
