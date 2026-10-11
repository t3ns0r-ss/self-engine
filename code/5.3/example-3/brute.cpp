#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    while (m--) {
        int k;
        long long x;
        cin >> k >> x;
        a[k - 1] = x;
        long long best = 0;
        for (int i = 0; i < n; i++) {
            long long s = 0;
            for (int j = i; j < n; j++) s += a[j], best = max(best, s);
        }
        cout << best << "\n";
    }
}
