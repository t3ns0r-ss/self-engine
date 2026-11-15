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
        map<int, long long> c;
        for (int i = l - 1; i < r; i++) c[a[i]]++;
        long long s = 0;
        for (auto [v, k] : c) s += (long long)v * k * k;
        cout << s << "\n";
    }
}
