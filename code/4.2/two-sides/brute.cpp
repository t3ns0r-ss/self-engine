#include <bits/stdc++.h>
using namespace std;

// Try all 2^n assignments of the two sides.
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (auto [a, b] : edges)
            if ((mask >> (a - 1) & 1) == (mask >> (b - 1) & 1)) ok = false;
        if (ok) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
}
