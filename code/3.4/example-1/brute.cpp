// Brute force: every subset of books as a bitmask.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n);
    for (int& p : h) cin >> p;
    for (int& p : s) cin >> p;
    int best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int price = 0, pages = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) {
                price += h[i];
                pages += s[i];
            }
        if (price <= x) best = max(best, pages);
    }
    cout << best << "\n";
}
