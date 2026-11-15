// Brute force: every subset as a bitmask; sort it and check that it is a chain.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> e(n);
    for (auto& p : e) cin >> p.first >> p.second;
    int best = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        vector<pair<int, int>> s;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s.push_back(e[i]);
        sort(s.begin(), s.end());
        bool ok = true;
        for (size_t i = 1; i < s.size(); i++)
            if (!(s[i - 1].first < s[i].first && s[i - 1].second < s[i].second)) ok = false;
        if (ok) best = max(best, (int)s.size());
    }
    cout << best << "\n";
}
