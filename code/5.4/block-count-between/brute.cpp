#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, x;
            cin >> k >> x;
            a[k - 1] = x;
        } else {
            int l, r, lo, hi, cnt = 0;
            cin >> l >> r >> lo >> hi;
            for (int i = l - 1; i < r; i++) cnt += lo <= a[i] && a[i] <= hi;
            cout << cnt << "\n";
        }
    }
}
