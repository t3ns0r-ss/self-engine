#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    while (q--) {
        int p, k;
        cin >> p >> k;
        long long s = 0;
        for (int i = p - 1; i < n; i += k) s += a[i];
        cout << s << "\n";
    }
}
