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
        long long cnt = 0;
        for (int i = l - 1; i < r; i++)
            for (int j = i + 1; j < r; j++) cnt += a[i] == a[j];
        cout << cnt << "\n";
    }
}
