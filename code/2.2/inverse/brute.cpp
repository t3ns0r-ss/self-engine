#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long a, m;
        cin >> a >> m;
        long long ans = -1;
        for (long long x = 0; x < m; x++)
            if ((__int128)(a % m) * x % m == 1 % m) {
                ans = x;
                break;
            }
        cout << ans << "\n";
    }
}
