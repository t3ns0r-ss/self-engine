// Largest disjoint subset by trying all subsets; fewest hitting points by trying all subsets of
// the interval ends (some optimal set of points uses only ends: move each point right to the
// nearest end of an interval containing it).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> s(n), e(n);
    for (int i = 0; i < n; i++) cin >> s[i] >> e[i];
    int best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int i = 0; i < n && ok; i++)
            for (int j = i + 1; j < n && ok; j++)
                if ((mask >> i & 1) && (mask >> j & 1) && max(s[i], s[j]) <= min(e[i], e[j])) ok = false;
        if (ok) best = max(best, __builtin_popcount(mask));
    }
    int fewest = n;
    for (int mask = 1; mask < (1 << n); mask++) {
        bool all = true;
        for (int i = 0; i < n && all; i++) {
            bool hit = false;
            for (int j = 0; j < n; j++)
                if ((mask >> j & 1) && s[i] <= e[j] && e[j] <= e[i]) hit = true;
            all = hit;
        }
        if (all) fewest = min(fewest, __builtin_popcount(mask));
    }
    cout << best << " " << fewest << "\n";
}
