/*
Brute force for teleporter-path: try every order of the teleporters as a walk that starts at level 1.
Prints the number of levels of a route that ends at level n, or IMPOSSIBLE.
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<pair<int, int>> teleporters;
vector<bool> used;

bool go(int at, int count) {
    if (count == m) return at == n;
    for (int i = 0; i < m; i++) {
        if (used[i] || teleporters[i].first != at) continue;
        used[i] = true;
        bool ok = go(teleporters[i].second, count + 1);
        used[i] = false;
        if (ok) return true;
    }
    return false;
}

int main() {
    cin >> n >> m;
    teleporters.resize(m);
    used.assign(m, false);
    for (auto& [a, b] : teleporters) cin >> a >> b;
    if (go(1, 0)) cout << m + 1 << "\n";
    else cout << "IMPOSSIBLE\n";
}
