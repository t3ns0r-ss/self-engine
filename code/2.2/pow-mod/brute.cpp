#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long a, b, m;
        cin >> a >> b >> m;
        __int128 r = 1 % m;
        for (long long i = 0; i < b; i++) r = r * (a % m) % m;
        cout << (long long)r << "\n";
    }
}
