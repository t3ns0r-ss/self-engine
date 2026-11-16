#include <bits/stdc++.h>
using namespace std;

/*
Problem: a bipartite graph with L left and R right vertices and m edges. Find the size of a largest matching and the size of a largest
set of vertices with no edge between two of them (an independent set).
Input: L R m, then m lines u v (left vertex 1..L, right vertex 1..R).
Output: two numbers: the size of a largest matching and the size of a largest independent set.
*/

// Kuhn's algorithm (Theorem 7.9.6).
struct Matching {
    vector<vector<int>> adj;
    vector<int> matchOf;
    vector<bool> seen;
    Matching(int L, int R) : adj(L), matchOf(R, -1), seen(R) {}
    bool tryAugment(int u) {
        for (int v : adj[u]) {
            if (seen[v]) continue;
            seen[v] = true;
            if (matchOf[v] < 0 || tryAugment(matchOf[v])) { matchOf[v] = u; return true; }
        }
        return false;
    }
    int solve() {
        int size = 0;
        for (int u = 0; u < (int)adj.size(); u++) {
            fill(seen.begin(), seen.end(), false);
            size += tryAugment(u);
        }
        return size;
    }
};

// snippet:begin
// A minimum vertex cover from a largest matching (Theorem 7.9.7). Call after m.solve().
// A vertex is reached when an alternating path from an unpaired left vertex gets to it. The cover is the left vertices
// that are not reached, plus the right vertices that are reached. Returns the left part in coverLeft and the right part in coverRight.
void minVertexCover(const Matching& m, int R, vector<int>& coverLeft, vector<int>& coverRight) {
    int L = m.adj.size();
    vector<bool> paired(L, false), leftReached(L, false), rightReached(R, false);
    for (int v = 0; v < R; v++)
        if (m.matchOf[v] >= 0) paired[m.matchOf[v]] = true;
    function<void(int)> walk = [&](int u) {  // u is a left vertex that has just been reached
        leftReached[u] = true;
        for (int v : m.adj[u]) {
            if (rightReached[v]) continue;
            rightReached[v] = true;
            if (m.matchOf[v] >= 0 && !leftReached[m.matchOf[v]]) walk(m.matchOf[v]);
        }
    };
    for (int u = 0; u < L; u++)
        if (!paired[u]) walk(u);
    for (int u = 0; u < L; u++)
        if (!leftReached[u]) coverLeft.push_back(u);
    for (int v = 0; v < R; v++)
        if (rightReached[v]) coverRight.push_back(v);
}
// snippet:end

int main() {
    int L, R, m;
    cin >> L >> R >> m;
    Matching mt(L, R);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        mt.adj[u - 1].push_back(v - 1);
    }
    int size = mt.solve();
    vector<int> coverLeft, coverRight;
    minVertexCover(mt, R, coverLeft, coverRight);
    vector<bool> inLeft(L, false), inRight(R, false);
    for (int u : coverLeft) inLeft[u] = true;
    for (int v : coverRight) inRight[v] = true;
    bool valid = (int)(coverLeft.size() + coverRight.size()) == size;  // the cover has exactly as many vertices as the matching has pairs
    for (int u = 0; u < L; u++)
        for (int v : mt.adj[u])
            if (!inLeft[u] && !inRight[v]) valid = false;  // an edge with no end in the cover
    if (!valid) { cout << "INVALID COVER\n"; return 0; }
    cout << size << " " << L + R - (int)(coverLeft.size() + coverRight.size()) << "\n";
}
