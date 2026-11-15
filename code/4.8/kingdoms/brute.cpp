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
    int count = 0;
    vector<int> kingdom(n + 1, 0);
    for (int v = 1; v <= n; v++) {
        for (int u = 1; u < v; u++)
            if (reach[u][v] && reach[v][u]) kingdom[v] = kingdom[u];
        if (!kingdom[v]) kingdom[v] = ++count;
    }
    cout << count << "\n";
    for (int v = 1; v <= n; v++) cout << kingdom[v] << (v < n ? ' ' : '\n');
}
