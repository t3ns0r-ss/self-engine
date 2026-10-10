/*
Problem: lowest common boss.
Input: n q, then p_2..p_n (the boss of employee i is p_i < i; employee 1 is the top boss), then q lines "a b".
Output: for each query, the lowest employee who is a boss of both a and b (an employee counts as his own boss).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.6.2 when every boss has a smaller number: depths and the table come straight from the parent array. Employees are 1..n.
vector<int> lowestCommonBosses(const vector<int>& parent, const vector<pair<int, int>>& queries) {
    int n = parent.size() - 1, levels = 1;
    while ((1 << levels) <= n) levels++;
    vector<int> depth(n + 1, 0);
    vector<vector<int>> up(levels, vector<int>(n + 1, 0));
    for (int v = 2; v <= n; v++) depth[v] = depth[parent[v]] + 1, up[0][v] = parent[v];  // the boss has a smaller number: already known
    for (int j = 1; j < levels; j++)
        for (int v = 1; v <= n; v++) up[j][v] = up[j - 1][up[j - 1][v]];
    vector<int> answer;
    for (auto [a, b] : queries) {
        if (depth[a] < depth[b]) swap(a, b);
        for (int j = 0; j < levels; j++)
            if ((depth[a] - depth[b]) >> j & 1) a = up[j][a];  // lift the deeper one
        if (a != b)
            for (int j = levels - 1; j >= 0; j--)
                if (up[j][a] != up[j][b]) a = up[j][a], b = up[j][b];
        answer.push_back(a == b ? a : up[0][a]);
    }
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; i++) cin >> parent[i];
    vector<pair<int, int>> queries(q);
    for (auto& x : queries) cin >> x.first >> x.second;
    for (int a : lowestCommonBosses(parent, queries)) cout << a << "\n";
}
