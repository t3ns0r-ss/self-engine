#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    while (m--) {
        int l, r;
        cin >> l >> r;
        map<int, int> c;
        for (int i = l - 1; i < r; i++) c[a[i]]++;
        int cnt = 0;
        for (auto [x, k] : c) cnt += x == k;
        cout << cnt << "\n";
    }
}
