#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 1857 style. A directed graph of n vertices and m edges (up to 10^5), each vertex with a letter a to z. The value of a
path is the number of times its most frequent letter occurs on it. Print the largest value of a path, or -1 if the graph has a cycle.
Input: n, m, the string of n letters, then the m edges "a b".
Output: the value or -1.
*/

vector<int> topologicalOrder(const vector<vector<int>>& out, vector<int> indeg) {
    int n = out.size();
    vector<int> order;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) order.push_back(v);
    for (size_t i = 0; i < order.size(); i++)
        for (int u : out[order[i]])
            if (--indeg[u] == 0) order.push_back(u);
    return order;
}

// snippet:begin
// Theorem 7.2.1 with a second dimension: dp[v][c] = the largest number of vertices with the letter c on a path that ends at v.
// If fewer than n vertices can be taken in topological order there is a cycle.
int largestLetterCount(const vector<vector<int>>& out, const vector<int>& order, const string& letters) {
    int n = out.size();
    if ((int)order.size() < n) return -1;
    vector<array<int, 26>> dp(n, array<int, 26>{});
    int best = 0;
    for (int v : order) {
        dp[v][letters[v] - 'a']++;  // v itself, after all edges into v have been merged
        for (int c = 0; c < 26; c++) best = max(best, dp[v][c]);
        for (int u : out[v])
            for (int c = 0; c < 26; c++) dp[u][c] = max(dp[u][c], dp[v][c]);
    }
    return best;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    string letters;
    cin >> letters;
    vector<vector<int>> out(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a - 1].push_back(b - 1), indeg[b - 1]++;
    }
    cout << largestLetterCount(out, topologicalOrder(out, indeg), letters) << "\n";
}
