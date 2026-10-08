#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long a, b, c;
        cin >> a >> b >> c;
        bool found = false;
        for (long long x = 0; x < b && !found; x++)  // x mod b covers every remainder
            if ((c - a * x) % b == 0) {
                cout << x << " " << (c - a * x) / b << "\n";
                found = true;
            }
        if (!found) cout << -1 << "\n";
    }
}
