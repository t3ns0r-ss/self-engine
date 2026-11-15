#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> iv(m);
    for (auto& x : iv) cin >> x[0] >> x[1] >> x[2];
    long long best = LLONG_MIN;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long total = 0;
        for (auto& x : iv)
            if (mask >> (x[0] - 1) & ((1 << (x[1] - x[0] + 1)) - 1)) total += x[2];
        best = max(best, total);
    }
    cout << best << "\n";
}
