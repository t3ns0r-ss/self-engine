#include <bits/stdc++.h>
using namespace std;

// Try all assignments in lexicographic order (pupil 1 is the most significant, team 1 is smaller than team 2); print the first valid one.
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    for (int code = 0; code < (1 << n); code++) {
        auto team = [&](int v) { return (code >> (n - v)) & 1; };
        bool ok = true;
        for (auto [a, b] : edges)
            if (team(a) == team(b)) ok = false;
        if (ok) {
            for (int v = 1; v <= n; v++) cout << (v > 1 ? " " : "") << team(v) + 1;
            cout << "\n";
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";
}
