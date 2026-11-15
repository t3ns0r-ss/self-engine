#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> speed(n), efficiency(n);
    for (int& x : speed) cin >> x;
    for (int& x : efficiency) cin >> x;
    long long best = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) > k) continue;
        long long sum = 0, low = INT_MAX;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) sum += speed[i], low = min<long long>(low, efficiency[i]);
        best = max(best, sum * low);
    }
    cout << best << "\n";
}
