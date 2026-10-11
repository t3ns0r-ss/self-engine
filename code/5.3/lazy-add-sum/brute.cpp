#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            long long d;
            cin >> d;
            for (int i = l - 1; i < r; i++) a[i] += d;
        } else {
            long long s = 0;
            for (int i = l - 1; i < r; i++) s += a[i];
            cout << s << "\n";
        }
    }
}
