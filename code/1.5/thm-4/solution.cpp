#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.4. The largest number of children satisfied: each child, by increasing greed, gets the smallest cookie that is big enough.
int satisfied(vector<int> g, vector<int> c) {
    sort(g.begin(), g.end());
    sort(c.begin(), c.end());
    int count = 0, j = 0;
    for (int greed : g) {
        while (j < (int)c.size() && c[j] < greed) j++;  // too small for this child, so for all later ones
        if (j == (int)c.size()) break;
        count++, j++;
    }
    return count;
}
// snippet:end

int main() {
    cout << "greed 1 2 3, cookies 1 1: " << satisfied({1, 2, 3}, {1, 1}) << " children\n";
    cout << "greed 1 2, cookies 1 2 3: " << satisfied({1, 2}, {1, 2, 3}) << " children\n";
    cout << "greed 5 6, cookies 1 2 3: " << satisfied({5, 6}, {1, 2, 3}) << " children\n";
    mt19937 rng(4);
    for (int round = 0; round < 400; round++) {
        int n = rng() % 5, m = rng() % 5;
        vector<int> g(n), c(m);
        for (int& x : g) x = rng() % 6 + 1;
        for (int& x : c) x = rng() % 6 + 1;
        int best = 0;  // every assignment: child i gets cookie p[i] or none
        vector<int> p(n, -1);
        function<void(int, int)> rec = [&](int i, int used) {
            if (i == n) { int s = 0; for (int k = 0; k < n; k++) s += p[k] >= 0; best = max(best, s); return; }
            p[i] = -1;
            rec(i + 1, used);
            for (int j = 0; j < m; j++) if (!(used >> j & 1) && c[j] >= g[i]) { p[i] = j; rec(i + 1, used | 1 << j); }
            p[i] = -1;
        };
        rec(0, 0);
        if (best != satisfied(g, c)) return 1;
    }
}
