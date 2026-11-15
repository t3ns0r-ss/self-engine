// Brute force: try every x in [0, m).
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, m;
    cin >> a >> b >> m;
    for (long long x = 0; x < m; x++)
        if ((__int128)a * x % m == b % m) {
            cout << x << "\n";
            return 0;
        }
    cout << -1 << "\n";
}
