// Brute force: try x = 0, 1, 2, ... up to the lcm.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> r(n), m(n);
    long long L = 1;
    for (int i = 0; i < n; i++) {
        cin >> r[i] >> m[i];
        L = L / __gcd(L, m[i]) * m[i];
    }
    for (long long x = 0; x < L; x++) {
        bool ok = true;
        for (int i = 0; i < n; i++) ok = ok && x % m[i] == r[i] % m[i];
        if (ok) {
            cout << x << " " << L << "\n";
            return 0;
        }
    }
    cout << -1 << "\n";
}
