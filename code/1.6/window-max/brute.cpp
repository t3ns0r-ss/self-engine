// Scans every window.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    for (int s = 0; s + k <= n; s++) {
        long long m = LLONG_MIN;
        for (int i = s; i < s + k; i++) m = max(m, a[i]);
        cout << m << (s + k < n ? ' ' : '\n');
    }
}
