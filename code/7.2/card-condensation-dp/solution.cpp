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

// method: the sum of the coins of a component, with the best of the components before it; brute: walks over (room, set visited) states.
long long method(const vector<vector<int>>& out, const vector<long long>& coins) {
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
long long brute(const vector<vector<int>>& out, const vector<long long>& coins) {
    int n = out.size();
    vector<char> seen(n << n, 0);
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
    vector<vector<int>> g1(6), g2(3), g3(2);
    for (auto [a, b] : vector<pair<int, int>>{{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}, {4, 3}, {2, 5}}) g1[a].push_back(b);
    for (auto [a, b] : vector<pair<int, int>>{{0, 1}, {1, 0}, {1, 2}}) g2[a].push_back(b);
    for (auto [a, b] : vector<pair<int, int>>{{0, 1}, {1, 0}}) g3[a].push_back(b);
    vector<long long> c1 = {2, 3, 1, 4, 1, 7}, c2 = {5, 5, 4}, c3 = {5, -3};
    cout << "P1 brute=" << brute(g1, c1) << " method=" << method(g1, c1) << "\n";
    cout << "P2 brute=" << brute(g2, c2) << " method=" << method(g2, c2) << "\n";
    // N1: a negative number of coins: the walk need not take the whole component (here it may stay in the room with 5).
    cout << "N1 brute=" << brute(g3, c3) << " method=" << method(g3, c3) << "\n";
}
