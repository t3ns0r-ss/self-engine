#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long x;
            cin >> k >> x;
            a[k - 1] = x;
        } else {
            int l, r;
            cin >> l >> r;
            long long best = LLONG_MAX;
            for (int i = l - 1; i < r; i++) best = min(best, a[i]);
            cout << best << "\n";
        }
    }
}
