/*
Problem: n children with greed g_i and m cookies with sizes c_j; a child is satisfied by one cookie of
size at least its greed, and each cookie goes to at most one child. Print the most satisfied children.
Input: n m (1 <= n, m <= 2*10^5), then g_1 .. g_n, then c_1 .. c_m (all between 1 and 10^9).
Output: the maximum number of satisfied children.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> g(n), c(m);
    for (auto& x : g) cin >> x;
    for (auto& x : c) cin >> x;
    sort(g.begin(), g.end());
    sort(c.begin(), c.end());
    int satisfied = 0, j = 0;  // j: the smallest cookie not yet given or skipped
    for (int i = 0; i < n; i++) {
        while (j < m && c[j] < g[i]) j++;  // too small for this child, so too small for all later ones
        if (j == m) break;                 // no cookie is large enough for anyone left
        satisfied++;                       // the smallest sufficient cookie (Theorem 1.5.4)
        j++;
    }
    cout << satisfied << "\n";
}
