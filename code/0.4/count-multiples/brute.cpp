// Tests every x in [l, r] with the mathematical remainder.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        long long l, r, k, cnt = 0;
        cin >> l >> r >> k;
        for (long long x = l; x <= r; x++)
            if (((x % k) + k) % k == 0) cnt++;
        cout << cnt << "\n";
    }
}
