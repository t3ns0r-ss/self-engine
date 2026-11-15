#include <bits/stdc++.h>
using namespace std;

// Try every set of stations and every set of links; keep the cheapest one in which every town is supplied.
int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> c(n);
    for (auto& x : c) cin >> x;
    vector<array<long long, 3>> links(m);
    for (auto& l : links) cin >> l[0] >> l[1] >> l[2];
    long long best = LLONG_MAX;
    for (int stations = 0; stations < (1 << n); stations++)
        for (int mask = 0; mask < (1 << m); mask++) {
            long long cost = 0;
            for (int i = 0; i < n; i++) if (stations >> i & 1) cost += c[i];
            for (int j = 0; j < m; j++) if (mask >> j & 1) cost += links[j][2];
            vector<bool> supplied(n + 1, false);
            for (int i = 0; i < n; i++) if (stations >> i & 1) supplied[i + 1] = true;
            for (bool changed = true; changed;) {  // supply spreads along the chosen links
                changed = false;
                for (int j = 0; j < m; j++)
                    if (mask >> j & 1) {
                        int a = links[j][0], b = links[j][1];
                        if (supplied[a] != supplied[b]) supplied[a] = supplied[b] = true, changed = true;
                    }
            }
            if (count(supplied.begin() + 1, supplied.end(), true) == n) best = min(best, cost);
        }
    cout << best << "\n";
}
