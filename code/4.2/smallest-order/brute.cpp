#include <bits/stdc++.h>
using namespace std;

// Try the permutations of the tasks in increasing order; the first one in which every rule holds is the smallest.
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> rules(m);
    for (auto& r : rules) cin >> r.first >> r.second;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    do {
        vector<int> position(n + 1);
        for (int i = 0; i < n; i++) position[perm[i]] = i;
        bool ok = true;
        for (auto [a, b] : rules)
            if (position[a] >= position[b]) ok = false;  // strictly before
        if (ok) {
            for (int i = 0; i < n; i++) cout << (i ? " " : "") << perm[i];
            cout << "\n";
            return 0;
        }
    } while (next_permutation(perm.begin(), perm.end()));
    cout << "IMPOSSIBLE\n";
}
