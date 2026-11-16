#include <bits/stdc++.h>
using namespace std;

/*
Problem: L left items and R right items; m allowed pairs (u, v) with u a left item and v a right item. Pair up as many as possible, each item in at most one pair.
Input: L R m, then m lines u v (left items 1..L, right items 1..R).
Output: the largest number of pairs.
*/

// snippet:begin
// Kuhn's algorithm (Theorem 7.9.6). Left vertices 0..L-1, right vertices 0..R-1; adj[u] lists the right vertices allowed for u.
struct Matching {
    vector<vector<int>> adj;
    vector<int> matchOf;  // matchOf[v]: the left vertex paired with right vertex v, or -1
    vector<bool> seen;    // right vertices visited by the current search
    Matching(int L, int R) : adj(L), matchOf(R, -1), seen(R) {}
    bool tryAugment(int u) {  // look for an augmenting path from the unpaired left vertex u, and flip it
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
            fill(seen.begin(), seen.end(), false);  // a fresh search for every left vertex
            size += tryAugment(u);
        }
        return size;
    }
};
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
    cout << mt.solve() << "\n";
}
