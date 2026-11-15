// Brute force: every subsequence as a bitmask; count the valid ones of the largest length.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    int best = 0;
    long long ways = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        int prev = 0, len = 0;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (!((mask >> i) & 1)) continue;
            if (len > 0 && a[i] <= prev) ok = false;
            prev = a[i];
            len++;
        }
        if (!ok) continue;
        if (len > best) best = len, ways = 1;
        else if (len == best) ways++;
    }
    cout << ways << "\n";
}
