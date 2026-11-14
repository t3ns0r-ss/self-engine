#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.8. The removal process in rounds: round 1 takes every vertex with no edge into it, round 2 every vertex
// that is free once round 1 is gone, and so on. The list of rounds is empty if a directed cycle blocks the process.
vector<vector<int>> rounds(const vector<vector<int>>& adj) {
    int n = adj.size() - 1, taken = 0;
    vector<int> indegree(n + 1, 0), current;
    for (int u = 1; u <= n; u++)
        for (int w : adj[u]) indegree[w]++;
    for (int v = 1; v <= n; v++)
        if (indegree[v] == 0) current.push_back(v);
    vector<vector<int>> result;
    while (!current.empty()) {
        result.push_back(current);
        taken += current.size();
        vector<int> following;  // vertices that become free when this round is removed
        for (int u : current)
            for (int w : adj[u])
                if (--indegree[w] == 0) following.push_back(w);
        current = following;
    }
    if (taken < n) result.clear();
    return result;
}
// snippet:end

void show(int n, vector<pair<int, int>> arrows) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : arrows) adj[a].push_back(b);
    vector<vector<int>> result = rounds(adj);
    if (result.empty()) {
        cout << "cycle: the process stops before every vertex is taken\n";
        return;
    }
    cout << "rounds:";
    for (size_t i = 0; i < result.size(); i++) {
        cout << (i ? " |" : "");
        for (int v : result[i]) cout << ' ' << v;
    }
    cout << "\n";
}

int main() {
    cout << "arrows 1>2 1>3 2>4 3>4: ";
    show(4, {{1, 2}, {1, 3}, {2, 4}, {3, 4}});
    cout << "arrows 4>2 2>1 1>3: ";
    show(4, {{4, 2}, {2, 1}, {1, 3}});
    cout << "arrows 1>2 2>3 3>2: ";
    show(3, {{1, 2}, {2, 3}, {3, 2}});
    // Check against the definitions on every directed graph with 4 vertices (2^12 of them): the round of v is the number of
    // vertices of a longest path ending at v, and the order is unique exactly when there are n rounds.
    int n = 4;
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= n; b++)
            if (a != b) pairs.push_back({a, b});
    for (int mask = 0; mask < (1 << pairs.size()); mask++) {
        vector<vector<int>> adj(n + 1);
        vector<pair<int, int>> arrows;
        for (size_t i = 0; i < pairs.size(); i++)
            if (mask >> i & 1) {
                adj[pairs[i].first].push_back(pairs[i].second);
                arrows.push_back(pairs[i]);
            }
        int orders = 0;
        vector<int> perm = {1, 2, 3, 4};
        do {
            int position[5];
            for (int i = 0; i < n; i++) position[perm[i]] = i;
            bool ok = true;
            for (auto [a, b] : arrows)
                if (position[a] > position[b]) ok = false;
            orders += ok;
        } while (next_permutation(perm.begin(), perm.end()));
        vector<vector<int>> result = rounds(adj);
        if (orders == 0) {
            if (!result.empty()) return 1;
            continue;
        }
        vector<int> longest(n + 1, 1);  // longest path ending at v, found by relaxing n times
        for (int pass = 0; pass < n; pass++)
            for (auto [a, b] : arrows) longest[b] = max(longest[b], longest[a] + 1);
        if (result.empty()) return 1;
        for (size_t r = 0; r < result.size(); r++)
            for (int v : result[r])
                if (longest[v] != (int)r + 1) return 1;
        if ((orders == 1) != ((int)result.size() == n)) return 1;
    }
}
