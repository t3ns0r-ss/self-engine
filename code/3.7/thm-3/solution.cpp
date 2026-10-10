#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.7.3. Packing into groups: best[mask] = the smallest pair (groups used, weight in the last group); the last item added
// goes into the last group or opens a new one.
pair<int, long long> packing(const vector<long long>& w, long long cap) {
    int n = w.size();
    vector<pair<int, long long>> best(1 << n, {INT_MAX, 0});
    best[0] = {1, 0};
    for (int mask = 1; mask < (1 << n); mask++)
        for (int j = 0; j < n; j++) {
            if (!(mask >> j & 1)) continue;
            auto [groups, fill] = best[mask ^ 1 << j];
            pair<int, long long> option = (fill + w[j] <= cap) ? make_pair(groups, fill + w[j]) : make_pair(groups + 1, w[j]);
            best[mask] = min(best[mask], option);
        }
    return best[(1 << n) - 1];
}
// snippet:end

int bruteGroups(const vector<long long>& w, long long cap, int i, vector<long long>& groups) {  // put each item in a group, recursively
    if (i == (int)w.size()) return groups.size();
    int best = INT_MAX;
    for (size_t g = 0; g < groups.size(); g++)
        if (groups[g] + w[i] <= cap) { groups[g] += w[i]; best = min(best, bruteGroups(w, cap, i + 1, groups)); groups[g] -= w[i]; }
    groups.push_back(w[i]);
    best = min(best, bruteGroups(w, cap, i + 1, groups));
    groups.pop_back();
    return best;
}
int main() {
    auto r = packing({4, 8, 6, 1}, 10);
    cout << "weights 4 8 6 1, capacity 10: " << r.first << " groups, last fill " << r.second << '\n';
    mt19937 rng(63);
    for (int round = 0; round < 200; round++) {
        int n = 1 + rng() % 8;
        long long cap = 5 + rng() % 8;
        vector<long long> w(n);
        for (auto& x : w) x = 1 + rng() % cap;
        vector<long long> groups;
        if (packing(w, cap).first != bruteGroups(w, cap, 0, groups)) return 1;
    }
}
