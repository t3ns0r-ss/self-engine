#include <bits/stdc++.h>
using namespace std;

const int N = 5;
vector<int> adj[N];  // adj[u]: the right vertices that left vertex u may be paired with
int matchOf[N];      // matchOf[v]: the left vertex paired with right vertex v, or -1
bool seen[N];

// Kuhn's algorithm from Theorem 7.9.6.
bool tryAugment(int u) {
    for (int v : adj[u]) {
        if (seen[v]) continue;
        seen[v] = true;
        if (matchOf[v] < 0 || tryAugment(matchOf[v])) { matchOf[v] = u; return true; }
    }
    return false;
}
int kuhn(int L, int R) {
    fill(matchOf, matchOf + R, -1);
    int size = 0;
    for (int u = 0; u < L; u++) { fill(seen, seen + R, false); size += tryAugment(u); }
    return size;
}

// snippet:begin
// Theorem 7.9.7. Run after kuhn. A vertex is "reached" when an alternating path from an unpaired left vertex gets to it:
// from a left vertex along any edge to a right vertex, from a right vertex along its matching edge to a left vertex.
// A minimum vertex cover: the left vertices not reached, and the right vertices reached.
void minVertexCover(int L, int R, vector<int>& coverLeft, vector<int>& coverRight) {
    vector<bool> pairedLeft(L, false), leftReached(L, false), rightReached(R, false);
    for (int v = 0; v < R; v++)
        if (matchOf[v] >= 0) pairedLeft[matchOf[v]] = true;
    function<void(int)> walk = [&](int u) {  // u is a left vertex that has just been reached
        leftReached[u] = true;
        for (int v : adj[u]) {
            if (rightReached[v]) continue;
            rightReached[v] = true;
            if (matchOf[v] >= 0 && !leftReached[matchOf[v]]) walk(matchOf[v]);
        }
    };
    for (int u = 0; u < L; u++)
        if (!pairedLeft[u]) walk(u);
    for (int u = 0; u < L; u++)
        if (!leftReached[u]) coverLeft.push_back(u);
    for (int v = 0; v < R; v++)
        if (rightReached[v]) coverRight.push_back(v);
}
// snippet:end

// Smallest vertex cover by trying every set of vertices (bit u: left vertex u, bit L + v: right vertex v).
int bruteCoverSize(int L, int R) {
    int best = L + R;
    for (int mask = 0; mask < (1 << (L + R)); mask++) {
        bool ok = true;
        for (int u = 0; u < L && ok; u++)
            for (int v : adj[u])
                if (!(mask >> u & 1) && !(mask >> (L + v) & 1)) { ok = false; break; }
        if (ok) best = min(best, __builtin_popcount(mask));
    }
    return best;
}

bool covers(int L, const vector<int>& coverLeft, const vector<int>& coverRight) {
    vector<bool> inLeft(N, false), inRight(N, false);
    for (int u : coverLeft) inLeft[u] = true;
    for (int v : coverRight) inRight[v] = true;
    for (int u = 0; u < L; u++)
        for (int v : adj[u])
            if (!inLeft[u] && !inRight[v]) return false;
    return true;
}

int main() {
    auto show = [&](const char* name, int L, int R, vector<vector<int>> lists) {
        for (int u = 0; u < N; u++) adj[u].clear();
        for (int u = 0; u < L; u++) adj[u] = lists[u];
        int size = kuhn(L, R);
        vector<int> coverLeft, coverRight;
        minVertexCover(L, R, coverLeft, coverRight);
        cout << name << ": matching = " << size << ", cover: left {";
        for (size_t i = 0; i < coverLeft.size(); i++) cout << (i ? "," : "") << coverLeft[i];
        cout << "} right {";
        for (size_t i = 0; i < coverRight.size(); i++) cout << (i ? "," : "") << coverRight[i];
        int cover = (int)(coverLeft.size() + coverRight.size());
        cout << "}, largest independent set = " << L + R - cover << "\n";
        if (cover != size || cover != bruteCoverSize(L, R) || !covers(L, coverLeft, coverRight)) exit(1);
    };
    show("coin grid", 3, 3, {{0, 1}, {0}, {2}});
    show("a star", 3, 3, {{0, 1, 2}, {0}, {0}});
    show("no edges", 2, 3, {{}, {}});

    // Check every bipartite graph with 1 to 4 vertices on each side: the cover is valid, and its size equals the size of
    // the largest matching and the size of the smallest vertex cover found by trying every set of vertices.
    for (int L = 1; L <= 4; L++)
        for (int R = 1; R <= 4; R++)
            for (int code = 0; code < (1 << (L * R)); code++) {
                for (int u = 0; u < N; u++) adj[u].clear();
                for (int i = 0; i < L; i++)
                    for (int j = 0; j < R; j++)
                        if (code >> (i * R + j) & 1) adj[i].push_back(j);
                int size = kuhn(L, R);
                vector<int> coverLeft, coverRight;
                minVertexCover(L, R, coverLeft, coverRight);
                if ((int)(coverLeft.size() + coverRight.size()) != size || !covers(L, coverLeft, coverRight) || size != bruteCoverSize(L, R)) return 1;
            }
}
