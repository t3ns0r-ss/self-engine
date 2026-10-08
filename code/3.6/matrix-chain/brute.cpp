// Brute force: try every bracketing by plain recursion (no table), trying every last multiplication.
#include <bits/stdc++.h>
using namespace std;

vector<long long> d;

long long solve(int l, int r) {
    if (l == r) return 0;
    long long best = LLONG_MAX;
    for (int k = l; k < r; k++) best = min(best, solve(l, k) + solve(k + 1, r) + d[l - 1] * d[k] * d[r]);
    return best;
}

int main() {
    int n;
    cin >> n;
    d.resize(n + 1);
    for (auto& x : d) cin >> x;
    cout << solve(1, n) << "\n";
}
