/*
Problem: AtCoder ABC 054 C One-stroke Path. Count the paths that start at vertex 1 and visit every
vertex of an undirected graph exactly once.
Input: N M (2 <= N <= 8), then M edges a b (1 <= a < b <= N, no repeated edges).
Output: the number of such paths.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Paths that start at vertex 0 and visit every vertex exactly once: try every order of the other vertices.
int countPaths(const vector<vector<bool>>& adj) {
    int n = adj.size(), count = 0;
    vector<int> rest;  // the order of the other vertices decides the path; vertex 0 is always first
    for (int v = 1; v < n; v++) rest.push_back(v);
    do {
        bool ok = adj[0][rest[0]];
        for (int i = 0; i + 1 < (int)rest.size() && ok; i++) ok = adj[rest[i]][rest[i + 1]];
        if (ok) count++;
    } while (next_permutation(rest.begin(), rest.end()));  // starts sorted
    return count;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> adj(n, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a][b] = adj[b][a] = true;
    }
    cout << countPaths(adj) << "\n";
}
