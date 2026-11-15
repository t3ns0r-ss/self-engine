#include <bits/stdc++.h>
using namespace std;

// Floyd-Warshall for the distances; then every order of visiting the cities, adding the distances between consecutive cities.
int main() {
    int n;
    cin >> n;
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
    for (int v = 1; v <= n; v++) d[v][v] = 0;
    for (int i = 0; i + 1 < n; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        d[a][b] = d[b][a] = min(d[a][b], c);
    }
    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    long long best = LLONG_MAX;
    do {
        long long total = 0;
        for (int i = 0; i + 1 < n; i++) total += d[order[i]][order[i + 1]];
        best = min(best, total);
    } while (next_permutation(order.begin(), order.end()));
    cout << best << "\n";
}
