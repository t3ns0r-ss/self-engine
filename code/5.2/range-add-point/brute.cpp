#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            long long d;
            cin >> l >> r >> d;
            for (int i = l; i <= r; i++) a[i] += d;
        } else {
            int k;
            cin >> k;
            cout << a[k] << "\n";
        }
    }
}
