#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q, k;
    cin >> n >> q >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    while (q--) {
        int l, r;
        cin >> l >> r;
        long long cnt = 0;
        for (int i = l - 1; i < r; i++) {
            int x = 0;
            for (int j = i; j < r; j++) {
                x ^= a[j];
                cnt += x == k;
            }
        }
        cout << cnt << "\n";
    }
}
