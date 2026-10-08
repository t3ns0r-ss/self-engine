// Brute force: every subset as a bitmask is one group.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int total = 0;
    for (int& x : a) {
        cin >> x;
        total += x;
    }
    int best = INT_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        int s = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s += a[i];
        best = min(best, abs(total - 2 * s));
    }
    cout << best << "\n";
}
