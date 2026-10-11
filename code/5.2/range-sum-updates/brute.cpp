#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long d;
            cin >> k >> d;
            a[k] += d;
        } else {
            int x, y;
            cin >> x >> y;
            long long s = 0;
            for (int i = x; i <= y; i++) s += a[i];
            cout << s << "\n";
        }
    }
}
