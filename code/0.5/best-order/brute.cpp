// Recursion: choose the next unvisited place at every step.
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<long long>> w;
vector<bool> used;

long long go(int last, int count) {
    if (count == n) return 0;
    long long best = LLONG_MAX;
    for (int v = 0; v < n; v++)
        if (!used[v]) {
            used[v] = true;
            long long step = last < 0 ? 0 : w[last][v];
            best = min(best, step + go(v, count + 1));
            used[v] = false;
        }
    return best;
}

int main() {
    cin >> n;
    w.assign(n, vector<long long>(n));
    for (auto& row : w)
        for (auto& x : row) cin >> x;
    used.assign(n, false);
    cout << go(-1, 0) << "\n";
}
