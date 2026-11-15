/*
Problem: AtCoder ABC 185 E, Sequence Matching. Remove elements from A (length N) and from B (length M) so that the
rest have equal length; the cost is the number of removed elements plus the number of positions where the rests
differ. Print the minimum cost.
Input: N M (N, M <= 1000), then A, then B (values <= 10^9).
Output: the minimum cost.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// ABC 185 E. E[i][j] = the minimum cost for the prefixes a_1..a_i and b_1..b_j: remove a_i, remove b_j, or keep both
// (cost 1 when they differ).
int sequenceMatching(const vector<long long>& a, const vector<long long>& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> E(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) E[i][0] = i;  // remove all i elements of a
    for (int j = 0; j <= m; j++) E[0][j] = j;  // remove all j elements of b
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            E[i][j] = min({E[i - 1][j] + 1, E[i][j - 1] + 1, E[i - 1][j - 1] + (a[i - 1] != b[j - 1])});
    return E[n][m];
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    cout << sequenceMatching(a, b) << "\n";
}
