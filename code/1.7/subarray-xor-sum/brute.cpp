#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long total = 0;
    for (int l = 0; l < n; l++) {
        long long x = 0;
        for (int r = l; r < n; r++) {
            x ^= a[r];
            total += x;
        }
    }
    cout << total << "\n";
}
