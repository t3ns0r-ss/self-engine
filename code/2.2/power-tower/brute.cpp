#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long a, b, c, p;
        cin >> a >> b >> c >> p;
        long long E = 1;  // b^c exactly (small in the tests)
        for (long long i = 0; i < c; i++) E *= b;
        long long r = 1 % p;
        for (long long i = 0; i < E; i++) r = r * (a % p) % p;
        cout << r << "\n";
    }
}
