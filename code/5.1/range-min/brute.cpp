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
        int best = a[l - 1];
        for (int i = l - 1; i < r; i++) best = min(best, a[i]);
        cout << best << "\n";
    }
}
