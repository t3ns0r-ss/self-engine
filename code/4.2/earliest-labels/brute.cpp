#include <bits/stdc++.h>
using namespace std;

// Try all orders; among the valid ones keep the one whose positions of course 1, 2, 3, ... are lexicographically smallest.
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> rules(m);
    for (auto& r : rules) cin >> r.first >> r.second;
    vector<int> perm(n), best, bestPositions;
    iota(perm.begin(), perm.end(), 1);
    do {
        vector<int> position(n + 1);
        for (int i = 0; i < n; i++) position[perm[i]] = i;
        bool ok = true;
        for (auto [a, b] : rules)
            if (position[a] >= position[b]) ok = false;
        if (!ok) continue;
        vector<int> positions(position.begin() + 1, position.end());
        if (best.empty() || positions < bestPositions) best = perm, bestPositions = positions;
    } while (next_permutation(perm.begin(), perm.end()));
    if (best.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < n; i++) cout << (i ? " " : "") << best[i];
    cout << "\n";
}
