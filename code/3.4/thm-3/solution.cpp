#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.3. A chain needs both keys to increase: sort by x, ties by y decreasing, then take the strict LIS of the y values.
int longestChain(vector<pair<int, int>> p) {
    sort(p.begin(), p.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first != b.first ? a.first < b.first : a.second > b.second;
    });
    vector<int> tails;
    for (auto& [x, y] : p) {
        auto it = lower_bound(tails.begin(), tails.end(), y);
        if (it == tails.end()) tails.push_back(y);
        else *it = y;
    }
    return tails.size();
}
// snippet:end

int main() {
    cout << "envelopes (5,4) (6,4) (6,7) (2,3): longest nesting " << longestChain({{5, 4}, {6, 4}, {6, 7}, {2, 3}}) << '\n';
    mt19937 rng(33);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 9;
        vector<pair<int, int>> p(n);
        for (auto& [x, y] : p) x = rng() % 5, y = rng() % 5;
        int best = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<pair<int, int>> s;
            for (int i = 0; i < n; i++) if (mask >> i & 1) s.push_back(p[i]);
            sort(s.begin(), s.end());
            bool ok = true;
            for (size_t i = 1; i < s.size(); i++) if (s[i].first <= s[i - 1].first || s[i].second <= s[i - 1].second) ok = false;
            if (ok) best = max(best, (int)s.size());
        }
        if (best != longestChain(p)) return 1;
    }
}
