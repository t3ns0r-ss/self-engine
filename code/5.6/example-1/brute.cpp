#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    while (q--) {
        int l, r;
        cin >> l >> r;
        map<int, int> c;
        int f = 0;
        for (int i = l - 1; i < r; i++) f = max(f, ++c[a[i]]);
        cout << max(1, 2 * f - (r - l + 1)) << "\n";
    }
}
