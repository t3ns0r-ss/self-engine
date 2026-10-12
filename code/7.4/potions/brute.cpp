#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    int best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long health = 0;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) health += a[i], ok &= health >= 0;
        if (ok) best = max(best, __builtin_popcount(mask));
    }
    cout << best << "\n";
}
