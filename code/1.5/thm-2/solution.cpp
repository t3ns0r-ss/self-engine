#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.2. Closed intervals (s, e), touching counts as overlapping. Earliest end first: the ends of the chosen intervals
// are the points; their number is both the most disjoint intervals and the fewest points that hit every interval.
vector<int> chosenEnds(vector<pair<int, int>> iv) {
    sort(iv.begin(), iv.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second; });
    vector<int> ends;
    int lastEnd = INT_MIN;
    for (auto [s, e] : iv)
        if (s > lastEnd) ends.push_back(e), lastEnd = e;  // compatible with everything chosen so far
    return ends;
}
// snippet:end

int main() {
    vector<pair<int, int>> iv = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}};
    cout << "chosen ends:";
    for (int e : chosenEnds(iv)) cout << ' ' << e;
    cout << '\n';
    cout << "[1,3] [2,4] [3,5]: " << chosenEnds({{1, 3}, {2, 4}, {3, 5}}).size() << " interval\n";
    mt19937 rng(2);
    for (int round = 0; round < 400; round++) {
        int n = rng() % 7 + 1;
        vector<pair<int, int>> v(n);
        for (auto& p : v) p.first = rng() % 10, p.second = p.first + rng() % 5;
        int bestSet = 0, bestPoints = INT_MAX;
        for (int mask = 0; mask < (1 << n); mask++) {
            bool ok = true;
            for (int i = 0; i < n && ok; i++) for (int j = i + 1; j < n && ok; j++)
                if ((mask >> i & 1) && (mask >> j & 1) && max(v[i].first, v[j].first) <= min(v[i].second, v[j].second)) ok = false;
            if (ok) bestSet = max(bestSet, __builtin_popcount(mask));
        }
        for (int mask = 0; mask < (1 << 15); mask++) {  // points among 0..14
            bool all = true;
            for (auto [s, e] : v) {
                bool hit = false;
                for (int x = s; x <= e; x++) hit |= mask >> x & 1;
                all &= hit;
            }
            if (all) bestPoints = min(bestPoints, __builtin_popcount(mask));
        }
        if ((int)chosenEnds(v).size() != bestSet || bestSet != bestPoints) return 1;
    }
}
