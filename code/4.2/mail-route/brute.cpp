/*
Brute force for mail-route: try every order of the streets (each in both directions) as a walk that starts at crossing 1.
Prints the number of crossings of a route that returns to crossing 1, or IMPOSSIBLE.
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<pair<int, int>> streets;
vector<bool> used;

bool go(int at, int count) {
    if (count == m) return at == 1;
    for (int i = 0; i < m; i++) {
        if (used[i]) continue;
        for (int side = 0; side < 2; side++) {
            int from = side == 0 ? streets[i].first : streets[i].second;
            int to = side == 0 ? streets[i].second : streets[i].first;
            if (from != at) continue;
            used[i] = true;
            bool ok = go(to, count + 1);
            used[i] = false;
            if (ok) return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    streets.resize(m);
    used.assign(m, false);
    for (auto& [a, b] : streets) cin >> a >> b;
    if (go(1, 0)) cout << m + 1 << "\n";
    else cout << "IMPOSSIBLE\n";
}
