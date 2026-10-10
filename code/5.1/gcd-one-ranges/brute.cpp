#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    long long total = 0;
    for (int l = 0; l < n; l++) {
        int g = 0;
        for (int r = l; r < n; r++) {
            g = __gcd(g, a[r]);
            total += g == 1;
        }
    }
    cout << total << "\n";
}
