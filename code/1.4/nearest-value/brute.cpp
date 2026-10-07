// Scans every value for every query.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    while (q--) {
        long long x;
        cin >> x;
        long long best = a[0];
        for (long long v : a)
            if (llabs(v - x) < llabs(best - x) || (llabs(v - x) == llabs(best - x) && v < best)) best = v;
        cout << best << "\n";
    }
}
