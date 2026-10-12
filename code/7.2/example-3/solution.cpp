#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1686, Coin Collector. A game has n rooms and m one-way tunnels (n up to 10^5, m up to 2·10^5), and every room has some
coins (up to 10^9). Moving through the tunnels, starting and ending in any rooms, what is the largest number of coins you can collect?
(A room's coins are taken the first time you are in it; rooms may be visited again.)
Input: n, m, the n coin numbers, then the tunnels "a b".
Output: the number (it needs 64 bits).
*/

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
// Theorem 7.2.3: the rooms of one strongly connected component can all be visited, so a component counts as one room with the sum of
// its coins; the components form a DAG, numbered here in topological order. best[c] = total[c] + the best of the components before c
// that have a tunnel into c.
long long collectCoins(const vector<vector<int>>& out, const vector<long long>& coins) {
    int n = out.size();
    vector<int> comp;
    int comps = stronglyConnected(out, comp);
    vector<long long> total(comps, 0), best(comps, 0);
    vector<vector<int>> from(comps);
    for (int v = 0; v < n; v++) {
        total[comp[v]] += coins[v];
        for (int u : out[v])
            if (comp[u] != comp[v]) from[comp[u]].push_back(comp[v]);
    }
    for (int c = 0; c < comps; c++) {
        for (int p : from[c]) best[c] = max(best[c], best[p]);
        best[c] += total[c];
    }
    return *max_element(best.begin(), best.end());
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> coins(n);
    for (auto& x : coins) cin >> x;
    vector<vector<int>> out(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a - 1].push_back(b - 1);
    }
    cout << collectCoins(out, coins) << "\n";
}
