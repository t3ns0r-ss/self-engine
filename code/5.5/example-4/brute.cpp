#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            for (int i = l - 1; i < r; i++) a[i] += x;
        } else {
            ll y;
            cin >> y;
            int first = -1, last = -1;
            for (int i = 0; i < n; i++)
                if (a[i] == y) {
                    if (first < 0) first = i;
                    last = i;
                }
            cout << (first < 0 ? -1 : last - first) << "\n";
        }
    }
}
