#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.7. A trail that uses every edge exactly once, as a list of vertices; empty if there is none.
// edges[i] = {a, b} (at least one edge; repeats and loops are allowed). It starts at an odd-degree vertex if there is one.
vector<int> eulerTrail(int n, const vector<pair<int, int>>& edges) {
    int m = edges.size();
    vector<vector<pair<int, int>>> adj(n + 1);  // adj[v] holds (other end, edge number)
    for (int i = 0; i < m; i++) {
        adj[edges[i].first].push_back({edges[i].second, i});
        adj[edges[i].second].push_back({edges[i].first, i});
    }
    int start = edges[0].first, odd = 0;
    for (int v = n; v >= 1; v--)  // counting down, so the smallest odd vertex is kept
        if (adj[v].size() % 2 == 1) odd++, start = v;
    if (odd != 0 && odd != 2) return {};
    vector<bool> used(m, false);
    vector<int> next(n + 1, 0), stack = {start}, trail;  // next[v]: first edge of adj[v] not yet tried
    while (!stack.empty()) {
        int v = stack.back();
        while (next[v] < (int)adj[v].size() && used[adj[v][next[v]].second]) next[v]++;
        if (next[v] == (int)adj[v].size()) {  // no unused edge: v is final
            trail.push_back(v);
            stack.pop_back();
        } else {
            used[adj[v][next[v]].second] = true;
            stack.push_back(adj[v][next[v]].first);
        }
    }
    if ((int)trail.size() != m + 1) return {};  // some edges lie in another component
    reverse(trail.begin(), trail.end());
    return trail;
}
// snippet:end

// Brute force: try every order of the edges, each in both directions, as a trail that starts anywhere.
bool someTrailExists(const vector<pair<int, int>>& edges, bool directed) {
    int m = edges.size();
    vector<bool> used(m, false);
    function<bool(int, int)> go = [&](int at, int count) {
        if (count == m) return true;
        for (int i = 0; i < m; i++) {
            if (used[i]) continue;
            for (int side = 0; side < (directed ? 1 : 2); side++) {
                int from = side == 0 ? edges[i].first : edges[i].second;
                int to = side == 0 ? edges[i].second : edges[i].first;
                if (from != at) continue;
                used[i] = true;
                bool ok = go(to, count + 1);
                used[i] = false;
                if (ok) return true;
            }
        }
        return false;
    };
    for (int v = 1; v <= 4; v++)
        if (go(v, 0)) return true;
    return false;
}

// A list of vertices is an Euler trail when consecutive vertices are joined by the edges, each edge used exactly once.
bool isEulerTrail(const vector<int>& trail, const vector<pair<int, int>>& edges) {
    multiset<pair<int, int>> left;
    for (auto [a, b] : edges) left.insert({min(a, b), max(a, b)});
    if (trail.size() != edges.size() + 1) return false;
    for (size_t i = 0; i + 1 < trail.size(); i++) {
        auto it = left.find({min(trail[i], trail[i + 1]), max(trail[i], trail[i + 1])});
        if (it == left.end()) return false;
        left.erase(it);
    }
    return true;
}

void show(const char* name, int n, const vector<pair<int, int>>& edges) {
    vector<int> trail = eulerTrail(n, edges);
    cout << name << ":";
    if (trail.empty()) cout << " none";
    for (int v : trail) cout << ' ' << v;
    cout << "\n";
}

int main() {
    show("edges 1-2 2-3 3-1 3-4", 4, {{1, 2}, {2, 3}, {3, 1}, {3, 4}});
    show("edges 1-2 1-2 2-3 3-4 4-2", 4, {{1, 2}, {1, 2}, {2, 3}, {3, 4}, {4, 2}});
    show("edges 1-2 2-3 3-1 4-5 5-6 6-4", 6, {{1, 2}, {2, 3}, {3, 1}, {4, 5}, {5, 6}, {6, 4}});
    // Check against the brute force on every multigraph with 4 vertices and at most 5 edges (loops included).
    vector<pair<int, int>> kinds;
    for (int a = 1; a <= 4; a++)
        for (int b = a; b <= 4; b++) kinds.push_back({a, b});
    vector<pair<int, int>> edges;
    function<int(int)> all = [&](int from) {
        // edges holds a multiset in non-decreasing order of kind; test it, then extend it
        if (!edges.empty()) {
            vector<int> trail = eulerTrail(4, edges);
            if (trail.empty() != !someTrailExists(edges, false)) return 1;
            if (!trail.empty() && !isEulerTrail(trail, edges)) return 1;
        }
        if (edges.size() == 5) return 0;
        for (int k = from; k < (int)kinds.size(); k++) {
            edges.push_back(kinds[k]);
            if (all(k)) return 1;
            edges.pop_back();
        }
        return 0;
    };
    if (all(0)) return 1;
    // Part (c): for arrows, the degree condition and one connected piece decide, checked on every multiset of at most 5 arrows
    // between 3 vertices (loops included).
    vector<pair<int, int>> arrowKinds, arrows;
    for (int a = 1; a <= 3; a++)
        for (int b = 1; b <= 3; b++) arrowKinds.push_back({a, b});
    function<int(int)> allArrows = [&](int from) {
        if (!arrows.empty()) {
            int balance[4] = {0, 0, 0, 0}, parent[4] = {0, 1, 2, 3}, plus = 0, minus = 0;
            function<int(int)> find = [&](int v) { return parent[v] == v ? v : parent[v] = find(parent[v]); };
            for (auto [a, b] : arrows) {
                balance[a]++, balance[b]--;
                parent[find(a)] = find(b);
            }
            bool balanced = true;
            for (int v = 1; v <= 3; v++) {
                if (balance[v] == 1) plus++;
                else if (balance[v] == -1) minus++;
                else if (balance[v] != 0) balanced = false;
            }
            int pieces = 0;
            vector<bool> seen(4, false), touched(4, false);
            for (auto [a, b] : arrows) touched[a] = touched[b] = true;
            for (int v = 1; v <= 3; v++)
                if (touched[v] && !seen[find(v)]) seen[find(v)] = true, pieces++;
            bool predicted = balanced && pieces == 1 && ((plus == 0 && minus == 0) || (plus == 1 && minus == 1));
            if (predicted != someTrailExists(arrows, true)) return 1;
        }
        if (arrows.size() == 5) return 0;
        for (int k = from; k < (int)arrowKinds.size(); k++) {
            arrows.push_back(arrowKinds[k]);
            if (allArrows(k)) return 1;
            arrows.pop_back();
        }
        return 0;
    };
    return allArrows(0);
}
