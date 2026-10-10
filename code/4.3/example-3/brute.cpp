#include <bits/stdc++.h>
using namespace std;

// Best walk of at most k edges, for k = n and for k = 3n: a walk with n or more edges repeats a room, and the best
// value grows between the two exactly when a positive cycle can be used.
int main() {
    int n, m;
    cin >> n >> m;
    const long long NEG = LLONG_MIN / 4;
    vector<array<long long, 3>> e(m);
    for (auto& x : e) cin >> x[0] >> x[1] >> x[2];
    vector<long long> best(n + 1, NEG);
    best[1] = 0;
    long long atN = NEG;
    for (int k = 1; k <= 3 * n; k++) {
        auto next = best;
        for (auto& x : e)
            if (best[x[0]] > NEG) next[x[1]] = max(next[x[1]], best[x[0]] + x[2]);
        best = next;
        if (k == n) atN = best[n];
    }
    cout << (best[n] != atN ? -1 : best[n]) << "\n";
}
