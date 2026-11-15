#include <bits/stdc++.h>
using namespace std;

int fewestGroups(const vector<long long>& w, long long cap) {
    int n = w.size();
    vector<pair<int, long long>> best(1 << n, {INT_MAX, 0});
    best[0] = {1, 0};
    for (int mask = 1; mask < (1 << n); mask++) for (int j = 0; j < n; j++) {
        if (!(mask >> j & 1)) continue;
        auto [groups, fill] = best[mask ^ 1 << j];
        pair<int, long long> option = (fill + w[j] <= cap) ? make_pair(groups, fill + w[j]) : make_pair(groups + 1, w[j]);
        best[mask] = min(best[mask], option);
    }
    return best[(1 << n) - 1].first;
}
int bruteGroups(const vector<long long>& w, long long cap, int i, vector<long long>& groups) {
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
    // P1: weights 4 8 6 1 with capacity 10. P2: five items of weight 5 with capacity 12. Brute: put each item in a group recursively.
    vector<long long> a = {4, 8, 6, 1}, b = {5, 5, 5, 5, 5};
    vector<long long> g1, g2;
    cout << "P1 brute=" << bruteGroups(a, 10, 0, g1) << " method=" << fewestGroups(a, 10) << '\n';
    cout << "P2 brute=" << bruteGroups(b, 12, 0, g2) << " method=" << fewestGroups(b, 12) << '\n';
    // N1: three items of weight 1 with capacity 3 and at most TWO items per group: boats. The mask table allows any number per group.
    cout << "N1 brute=" << 2 << " method=" << fewestGroups({1, 1, 1}, 3) << '\n';
    // N2: split 1, 2, ..., 40 into two groups of equal sum 410: subset sums decide it; a table over masks of 40 items has 2^40 entries.
    vector<char> reach(821, 0);
    reach[0] = 1;
    for (int k = 1; k <= 40; k++) for (int s = 820; s >= k; s--) reach[s] |= reach[s - k];
    cout << "N2 brute=" << (int)reach[410] << " method=" << (40 > 22 ? "too-slow" : "ok") << '\n';
}
