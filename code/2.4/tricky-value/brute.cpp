#include <bits/stdc++.h>
using namespace std;

// Brute force: every pair of positions, with g(i, j) summed entry by entry.
int main() {
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    long long best = LLONG_MAX;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            long long g = 0;
            for (int k = i + 1; k <= j; k++) g += a[k];
            best = min(best, (long long)(j - i) * (j - i) + g * g);
        }
    cout << best << "\n";
}
