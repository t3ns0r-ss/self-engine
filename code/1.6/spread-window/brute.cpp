// Every subarray, with running maximum and minimum.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long K;
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    int best = 0;
    for (int l = 0; l < n; l++) {
        long long mx = LLONG_MIN, mn = LLONG_MAX;
        for (int r = l; r < n; r++) {
            mx = max(mx, a[r]);
            mn = min(mn, a[r]);
            if (mx - mn <= K) best = max(best, r - l + 1);
        }
    }
    cout << best << "\n";
}
