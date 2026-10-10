#include <bits/stdc++.h>
using namespace std;

// Relax every way of clearing a stage, n times over.
int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> e;
    for (int i = 1; i < n; i++) {
        long long a, b, x;
        cin >> a >> b >> x;
        e.push_back({i, i + 1, a});
        e.push_back({i, x, b});
    }
    const long long INF = LLONG_MAX / 4;
    vector<long long> d(n + 1, INF);
    d[1] = 0;
    for (int r = 0; r < n; r++)
        for (auto& x : e)
            if (d[x[0]] < INF) d[x[1]] = min(d[x[1]], d[x[0]] + x[2]);
    cout << d[n] << "\n";
}
