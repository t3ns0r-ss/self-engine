#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
    for (int v = 1; v <= n; v++) reach[v][v] = true;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        reach[a][b] = true;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;
    int best = n;
    for (int mask = 1; mask < (1 << n); mask++) {
        bool all = true;
        for (int v = 1; v <= n; v++) {
            bool covered = false;
            for (int s = 0; s < n; s++) covered = covered || ((mask >> s & 1) && reach[s + 1][v]);
            all = all && covered;
        }
        if (all) best = min(best, __builtin_popcount(mask));
    }
    cout << best << "\n";
}
