#include <bits/stdc++.h>
using namespace std;

const int N = 5;
vector<int> adj[N];  // adj[u]: the right vertices that left vertex u may be paired with
int matchOf[N];      // matchOf[v]: the left vertex paired with right vertex v, or -1
bool seen[N];

// snippet:begin
// Theorem 7.9.6. Kuhn's algorithm. tryAugment(u) looks for an augmenting path that starts at the unpaired left vertex u
// (a path that alternates between non-matching and matching edges and ends at an unpaired right vertex) and flips it.
bool tryAugment(int u) {
    for (int v : adj[u]) {
        if (seen[v]) continue;  // each right vertex is visited at most once per search
        seen[v] = true;
        if (matchOf[v] < 0 || tryAugment(matchOf[v])) {  // v is free, or its partner can move to another right vertex
            matchOf[v] = u;
            return true;
        }
    }
    return false;
}
int kuhn(int L, int R) {  // the size of a largest matching
    fill(matchOf, matchOf + R, -1);
    int size = 0;
    for (int u = 0; u < L; u++) {  // each left vertex is tried once
        fill(seen, seen + R, false);
        size += tryAugment(u);
    }
    return size;
}
// snippet:end

int bruteMatching(int L, int R, int i, int usedRight) {
    if (i == L) return 0;
    int best = bruteMatching(L, R, i + 1, usedRight);
    for (int v : adj[i])
        if (!(usedRight >> v & 1)) best = max(best, 1 + bruteMatching(L, R, i + 1, usedRight | 1 << v));
    return best;
}

// True when some unpaired left vertex still has an augmenting path (it must never happen after kuhn).
bool someVertexCanStillAugment(int L, int R) {
    vector<bool> paired(L, false);
    for (int v = 0; v < R; v++)
        if (matchOf[v] >= 0) paired[matchOf[v]] = true;
    for (int u = 0; u < L; u++)
        if (!paired[u]) {
            fill(seen, seen + R, false);
            vector<int> saved(matchOf, matchOf + R);
            bool found = tryAugment(u);
            copy(saved.begin(), saved.end(), matchOf);
            if (found) return true;
        }
    return false;
}

int main() {
    auto show = [&](const char* name, int L, int R, vector<vector<int>> lists) {
        for (int u = 0; u < N; u++) adj[u].clear();
        for (int u = 0; u < L; u++) adj[u] = lists[u];
        int size = kuhn(L, R);
        cout << name << ": size = " << size << ", partner of right vertex 0.." << R - 1 << ":";
        for (int v = 0; v < R; v++) cout << " " << matchOf[v];
        cout << ", an unpaired left vertex can still augment: " << (someVertexCanStillAugment(L, R) ? "yes" : "no") << "\n";
        if (size != bruteMatching(L, R, 0, 0)) exit(1);
    };
    show("reroute", 3, 3, {{0, 1}, {0}, {0}});
    show("everyone fits", 3, 3, {{0}, {0, 1}, {1, 2}});
    show("one left over", 3, 2, {{0, 1}, {0, 1}, {0}});
    show("no edges", 2, 2, {{}, {}});

    // Check every bipartite graph with 1 to 4 vertices on each side.
    for (int L = 1; L <= 4; L++)
        for (int R = 1; R <= 4; R++)
            for (int code = 0; code < (1 << (L * R)); code++) {
                for (int u = 0; u < N; u++) adj[u].clear();
                for (int i = 0; i < L; i++)
                    for (int j = 0; j < R; j++)
                        if (code >> (i * R + j) & 1) adj[i].push_back(j);
                if (kuhn(L, R) != bruteMatching(L, R, 0, 0)) return 1;
                if (someVertexCanStillAugment(L, R)) return 1;
            }
}
