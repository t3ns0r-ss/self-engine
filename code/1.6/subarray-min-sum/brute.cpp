// Every subarray, with a running minimum.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long total = 0;
    for (int l = 0; l < n; l++) {
        long long m = LLONG_MAX;
        for (int r = l; r < n; r++) {
            m = min(m, a[r]);
            total += m;
        }
    }
    cout << total << "\n";
}
