#include <bits/stdc++.h>
using namespace std;

// Brute force: list every simple path from s to t, then find the largest family of pairwise disjoint paths.
int n, m, s, t;
vector<array<int, 2>> edges;
struct PathInfo { int edgeMask, innerMask; };
vector<PathInfo> paths;
void listPaths(int u, int visited, int edgeMask, int innerMask) {
    if (u == t) { paths.push_back({edgeMask, innerMask}); return; }
    for (int k = 0; k < m; k++)
        if (edges[k][0] == u && !(visited >> edges[k][1] & 1)) {
            int v = edges[k][1];
            listPaths(v, visited | 1 << v, edgeMask | 1 << k, v == t ? innerMask : innerMask | 1 << v);
        }
}
int family(size_t from, int usedEdges, int usedInner, bool vertexDisjoint) {
    int best = 0;
    for (size_t i = from; i < paths.size(); i++) {
        bool clash = (paths[i].edgeMask & usedEdges) != 0;           // sharing an edge is never allowed
        if (vertexDisjoint && (paths[i].innerMask & usedInner)) clash = true;
        if (!clash) best = max(best, 1 + family(i + 1, usedEdges | paths[i].edgeMask, usedInner | paths[i].innerMask, vertexDisjoint));
    }
    return best;
}
int main() {
    cin >> n >> m >> s >> t;
    s--; t--;
    edges.resize(m);
    for (auto& e : edges) {
        cin >> e[0] >> e[1];
        e[0]--; e[1]--;
    }
    listPaths(s, 1 << s, 0, 0);
    cout << family(0, 0, 0, false) << " " << family(0, 0, 0, true) << "\n";
}
