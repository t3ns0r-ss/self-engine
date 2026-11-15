#include <bits/stdc++.h>
using namespace std;

int main() {
    int target, startFuel, n;
    cin >> target >> startFuel >> n;
    vector<pair<int, int>> s(n);
    for (auto& [p, f] : s) cin >> p >> f;
    sort(s.begin(), s.end());
    int best = -1;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long reach = startFuel;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) ok &= s[i].first <= reach, reach += s[i].second;
        if (ok && reach >= target && (best < 0 || __builtin_popcount(mask) < best)) best = __builtin_popcount(mask);
    }
    cout << best << "\n";
}
