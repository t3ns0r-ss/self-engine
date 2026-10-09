// Brute force: try every permutation of the jobs.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> c(n, vector<long long>(n));
    for (auto& row : c)
        for (auto& x : row) cin >> x;
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    long long best = LLONG_MAX;
    do {
        long long cost = 0;
        for (int i = 0; i < n; i++) cost += c[i][p[i]];
        best = min(best, cost);
    } while (next_permutation(p.begin(), p.end()));
    cout << best << "\n";
}
