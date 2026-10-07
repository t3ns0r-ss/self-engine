// Tries every assignment: each child gets one unused cookie that satisfies it, or nothing.
#include <bits/stdc++.h>
using namespace std;

int n, m, best = 0;
vector<int> g, c;
vector<bool> used;

void go(int i, int count) {
    if (i == n) {
        best = max(best, count);
        return;
    }
    go(i + 1, count);  // child i gets nothing
    for (int j = 0; j < m; j++)
        if (!used[j] && c[j] >= g[i]) {
            used[j] = true;
            go(i + 1, count + 1);
            used[j] = false;
        }
}

int main() {
    cin >> n >> m;
    g.resize(n);
    c.resize(m);
    used.assign(m, false);
    for (auto& x : g) cin >> x;
    for (auto& x : c) cin >> x;
    go(0, 0);
    cout << best << "\n";
}
