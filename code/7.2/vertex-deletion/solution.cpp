#include <bits/stdc++.h>
using namespace std;

/*
Problem: a tree of n vertices (n up to 2·10^5). Count the vertices whose deletion (with its edges) leaves a maximum matching
of the same size as the maximum matching of the whole tree.
Input: n, then n - 1 edges.
Output: the count.
*/

// snippet:begin
// Theorem 7.2.2 with a pair per part: (the size of its maximum matching, whether its root is free in the greedy matching).
// A part is combined by sums and by a count of free roots, so the part of a child is left out by subtracting its own pair.
int countKeepingMatching(int n, const vector<vector<int>>& adj) {
    vector<int> parent(n, -1), order = {0};
    for (size_t i = 0; i < order.size(); i++)
        for (int c : adj[order[i]])
            if (c != parent[order[i]]) parent[c] = order[i], order.push_back(c);
    vector<int> match(n, 0), freeRoot(n, 1), freeKids(n, 0), sum(n, 0);  // match: of the subtree; freeKids, sum: over children
    for (int i = n - 1; i > 0; i--) {
        int v = order[i], p = parent[v];
        match[v] = sum[v] + (freeKids[v] > 0), freeRoot[v] = freeKids[v] == 0;
        sum[p] += match[v], freeKids[p] += freeRoot[v];
    }
    match[0] = sum[0] + (freeKids[0] > 0);
    vector<int> upMatch(n, 0), upFree(n, 0);  // the part above v (empty for the root: no free root)
    int whole = match[0], count = 0;
    for (int v : order) {
        int totalSum = sum[v] + upMatch[v], totalFree = freeKids[v] + upFree[v];
        count += totalSum == whole;  // deleting v leaves the parts around it
        for (int c : adj[v]) {
            if (c == parent[v]) continue;
            int otherFree = totalFree - freeRoot[c];  // the parts around v except the one of c
            upMatch[c] = totalSum - match[c] + (otherFree > 0), upFree[c] = otherFree == 0;
        }
    }
    return count;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b), adj[b].push_back(a);
    }
    cout << countKeepingMatching(n, adj) << "\n";
}
