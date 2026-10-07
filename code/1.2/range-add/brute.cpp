// Applies every update element by element.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n + 1, 0);
    while (q--) {
        int l, r;
        long long v;
        cin >> l >> r >> v;
        for (int i = l; i <= r; i++) a[i] += v;
    }
    for (int i = 1; i <= n; i++) cout << a[i] << (i < n ? ' ' : '\n');
}
