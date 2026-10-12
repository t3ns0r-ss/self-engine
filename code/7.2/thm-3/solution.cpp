#include <bits/stdc++.h>
using namespace std;

int stronglyConnected(const vector<vector<int>>& out, vector<int>& comp) {
    int n = out.size(), comps = 0;
    vector<vector<int>> in(n);
    for (int v = 0; v < n; v++)
        for (int u : out[v]) in[u].push_back(v);
    vector<int> finish, next(n, 0), stack;
    vector<char> seen(n, 0);
    for (int s = 0; s < n; s++) {  // first pass: the order of finishing on the graph
        if (seen[s]) continue;
        seen[s] = 1, stack = {s};
        while (!stack.empty()) {
            int v = stack.back();
            if (next[v] < (int)out[v].size()) {
                int u = out[v][next[v]++];
                if (!seen[u]) seen[u] = 1, stack.push_back(u);
            } else finish.push_back(v), stack.pop_back();
        }
    }
    comp.assign(n, -1);
    for (int i = n - 1; i >= 0; i--) {  // second pass on the reversed graph, last finished first
        int s = finish[i];
        if (comp[s] >= 0) continue;
        comp[s] = comps, stack = {s};
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            for (int u : in[v])
                if (comp[u] < 0) comp[u] = comps, stack.push_back(u);
        }
        comps++;
    }
    return comps;
}

// snippet:begin
// Theorem 7.2.3. The most coins collected on a walk that may visit rooms again (coins are taken once). comp[v] is the component of the
// room v, numbered in a topological order of the condensation, comps is their number.
long long mostCoins(const vector<vector<int>>& out, const vector<int>& comp, int comps, const vector<long long>& coins) {
    int n = out.size();
    vector<long long> total(comps, 0), best(comps, 0);
    vector<vector<int>> from(comps);  // from[c] = the components with an edge into c
    for (int v = 0; v < n; v++) {
        total[comp[v]] += coins[v];
        for (int u : out[v])
            if (comp[u] != comp[v]) from[comp[u]].push_back(comp[v]);
    }
    for (int c = 0; c < comps; c++) {  // all components before c are finished
        best[c] = 0;
        for (int p : from[c]) best[c] = max(best[c], best[p]);
        best[c] += total[c];
    }
    return *max_element(best.begin(), best.end());
}
// snippet:end

// Walks that may visit rooms again: a search over (room, set of rooms visited) states.
long long bruteCoins(const vector<vector<int>>& out, const vector<long long>& coins) {
    int n = out.size();
    vector<char> seen(n << n, 0);  // index = room * 2^n + mask
    long long best = 0;
    vector<pair<int, int>> stack;
    for (int s = 0; s < n; s++) stack.push_back({s, 1 << s}), seen[s << n | 1 << s] = 1;
    while (!stack.empty()) {
        auto [v, mask] = stack.back();
        stack.pop_back();
        long long sum = 0;
        for (int u = 0; u < n; u++)
            if (mask >> u & 1) sum += coins[u];
        best = max(best, sum);
        for (int u : out[v]) {
            int m2 = mask | 1 << u;
            if (!seen[u << n | m2]) seen[u << n | m2] = 1, stack.push_back({u, m2});
        }
    }
    return best;
}

int main() {
    vector<vector<int>> out(6);
    for (auto [a, b] : vector<pair<int, int>>{{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}, {4, 3}, {2, 5}}) out[a].push_back(b);
    vector<long long> coins = {2, 3, 1, 4, 1, 7};
    vector<int> comp;
    int comps = stronglyConnected(out, comp);
    cout << "components " << comps << ", of the rooms 0 to 5:";
    for (int c : comp) cout << " " << c;
    cout << "\nmost coins " << mostCoins(out, comp, comps, coins) << "\n";
    // Check (not printed): the same as the search over (room, visited set) states, for 3000 random graphs of up to 7 rooms with
    // cycles, coins 0 to 9, and every edge going forward in the numbering of the components.
    mt19937 rng(21);
    for (int it = 0; it < 3000; it++) {
        int n = 1 + rng() % 7;
        vector<vector<int>> g(n);
        for (int a = 0; a < n; a++)
            for (int b = 0; b < n; b++)
                if (a != b && rng() % 100 < 25) g[a].push_back(b);
        vector<long long> c(n);
        for (auto& x : c) x = rng() % 10;
        vector<int> cmp;
        int k = stronglyConnected(g, cmp);
        for (int a = 0; a < n; a++)
            for (int b : g[a])
                if (cmp[a] > cmp[b]) return 1;
        if (mostCoins(g, cmp, k, c) != bruteCoins(g, c)) return 1;
    }
}
