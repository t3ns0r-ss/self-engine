#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    int best = 0;
    for (int l = 0; l < n; l++) {
        int x = 0;
        for (int r = l; r < n; r++) {
            x ^= a[r];
            best = max(best, x);
        }
    }
    cout << best << "\n";
}
