// Every range of bars, with the running minimum height.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> h(n);
    for (auto& x : h) cin >> x;
    long long best = 0;
    for (int l = 0; l < n; l++) {
        long long m = LLONG_MAX;
        for (int r = l; r < n; r++) {
            m = min(m, h[r]);
            best = max(best, m * (r - l + 1));
        }
    }
    cout << best << "\n";
}
