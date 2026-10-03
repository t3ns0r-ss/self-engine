// Computes the exact sum in 128-bit integers, then takes the mathematical remainder.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long m;
    cin >> n >> m;
    __int128 s = 0;
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        s += (__int128)a * b;
    }
    __int128 r = s % m;
    if (r < 0) r += m;
    cout << (long long)r << "\n";
}
