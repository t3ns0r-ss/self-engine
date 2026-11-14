#include <bits/stdc++.h>
using namespace std;

// Brute force: is there a walk that uses every edge exactly once? Tries every order of the edges (and both directions for
// two-way edges), starting anywhere.
bool walkUsesEveryEdge(int n, const vector<pair<int, int>>& edges, bool directed) {
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
    for (int v = 1; v <= n; v++)
        if (go(v, 0)) return true;
    return false;
}

// Method of the card (Theorem 4.2.7): the number of odd-degree vertices is 0 or 2 (the arrows balance, up to one start and one
// end), and all edges lie in one connected piece. The flag `skipConnected` leaves out the second condition.
bool eulerTest(int n, const vector<pair<int, int>>& edges, bool directed, bool skipConnected) {
    vector<int> degree(n + 1, 0), balance(n + 1, 0), parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    function<int(int)> find = [&](int v) { return parent[v] == v ? v : parent[v] = find(parent[v]); };
    for (auto [a, b] : edges) {
        degree[a]++, degree[b]++;
        balance[a]++, balance[b]--;
        parent[find(a)] = find(b);
    }
    bool conditions;
    if (directed) {
        int plus = 0, minus = 0, other = 0;
        for (int v = 1; v <= n; v++) {
            if (balance[v] == 1) plus++;
            else if (balance[v] == -1) minus++;
            else if (balance[v] != 0) other++;
        }
        conditions = other == 0 && ((plus == 0 && minus == 0) || (plus == 1 && minus == 1));
    } else {
        int odd = 0;
        for (int v = 1; v <= n; v++) odd += degree[v] % 2;
        conditions = odd == 0 || odd == 2;
    }
    if (!conditions) return false;
    if (skipConnected) return true;
    int root = -1;
    for (int v = 1; v <= n; v++) {
        if (degree[v] == 0) continue;
        if (root == -1) root = find(v);
        if (find(v) != root) return false;
    }
    return true;
}

// Brute force for "visit every vertex exactly once": every order of the vertices, checked edge by edge.
bool pathVisitsEveryVertex(int n, const vector<pair<int, int>>& edges) {
    vector<vector<bool>> joined(n + 1, vector<bool>(n + 1, false));
    for (auto [a, b] : edges) joined[a][b] = joined[b][a] = true;
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    do {
        bool ok = true;
        for (int i = 0; i + 1 < n; i++)
            if (!joined[order[i]][order[i + 1]]) ok = false;
        if (ok) return true;
    } while (next_permutation(order.begin(), order.end()));
    return false;
}

string word(bool yes) { return yes ? "yes" : "no"; }

int main() {
    // P1: roads 1-2, 2-3, 3-1, 3-4: every road once? The odd-degree crossings are 3 and 4.
    vector<pair<int, int>> roads = {{1, 2}, {2, 3}, {3, 1}, {3, 4}};
    cout << "P1 brute=" << word(walkUsesEveryEdge(4, roads, false)) << " method=" << word(eulerTest(4, roads, false, false)) << "\n";
    // P2: arrows 1>2, 2>3, 3>1, 1>4, 4>1: one closed walk through every arrow? Every vertex has as many arrows in as out.
    vector<pair<int, int>> arrows = {{1, 2}, {2, 3}, {3, 1}, {1, 4}, {4, 1}};
    cout << "P2 brute=" << word(walkUsesEveryEdge(4, arrows, true)) << " method=" << word(eulerTest(4, arrows, true, false)) << "\n";
    // N1: two separate triangles. All degrees are even, but no walk can cross from one triangle to the other.
    vector<pair<int, int>> twoTriangles = {{1, 2}, {2, 3}, {3, 1}, {4, 5}, {5, 6}, {6, 4}};
    cout << "N1 brute=" << word(walkUsesEveryEdge(6, twoTriangles, false)) << " method=" << word(eulerTest(6, twoTriangles, false, true)) << "\n";
    // N2: the complete graph on 4 vertices; a walk that visits every VERTEX once exists, but the edge test (four odd degrees) says no.
    vector<pair<int, int>> k4 = {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};
    cout << "N2 brute=" << word(pathVisitsEveryVertex(4, k4)) << " method=" << word(eulerTest(4, k4, false, false)) << "\n";
}
