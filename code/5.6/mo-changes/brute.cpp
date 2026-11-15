#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, U, q;
    cin >> n >> U >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<array<int, 2>> changes(U);
    for (auto& c : changes) cin >> c[0] >> c[1], c[0]--;
    while (q--) {
        int l, r, t;
        cin >> l >> r >> t;
        vector<int> b = a;
        for (int k = 0; k < t; k++) b[changes[k][0]] = changes[k][1];
        map<int, long long> c;
        for (int i = l - 1; i < r; i++) c[b[i]]++;
        long long power = 0;
        for (auto [v, k] : c) power += v * k * k;
        cout << power << "\n";
    }
}
