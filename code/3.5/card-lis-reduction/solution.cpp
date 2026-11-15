#include <bits/stdc++.h>
using namespace std;

int lis(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) { auto it = lower_bound(tails.begin(), tails.end(), x); if (it == tails.end()) tails.push_back(x); else *it = x; }
    return tails.size();
}
int bruteLis(const vector<int>& a) {
    int best = 0, n = a.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        int last = INT_MIN, len = 0;
        bool ok = true;
        for (int i = 0; i < n && ok; i++) if (mask >> i & 1) { if (a[i] <= last) ok = false; last = a[i], len++; }
        if (ok) best = max(best, len);
    }
    return best;
}
int lcs(const string& a, const string& b) {
    vector<vector<int>> C(a.size() + 1, vector<int>(b.size() + 1, 0));
    for (size_t i = 1; i <= a.size(); i++) for (size_t j = 1; j <= b.size(); j++)
        C[i][j] = a[i - 1] == b[j - 1] ? C[i - 1][j - 1] + 1 : max(C[i - 1][j], C[i][j - 1]);
    return C[a.size()][b.size()];
}
int bruteLcs(const string& x, const string& y) {
    int best = 0;
    for (int mask = 0; mask < (1 << x.size()); mask++) {
        string s;
        for (size_t i = 0; i < x.size(); i++) if (mask >> i & 1) s += x[i];
        size_t p = 0;
        for (char ch : y) if (p < s.size() && s[p] == ch) p++;
        if (p == s.size()) best = max(best, (int)s.size());
    }
    return best;
}
int editDistance(const string& a, const string& b) {
    vector<vector<int>> E(a.size() + 1, vector<int>(b.size() + 1));
    for (size_t i = 0; i <= a.size(); i++) E[i][0] = i;
    for (size_t j = 0; j <= b.size(); j++) E[0][j] = j;
    for (size_t i = 1; i <= a.size(); i++) for (size_t j = 1; j <= b.size(); j++)
        E[i][j] = min({E[i - 1][j] + 1, E[i][j - 1] + 1, E[i - 1][j - 1] + (a[i - 1] != b[j - 1])});
    return E[a.size()][b.size()];
}
int chain(vector<pair<int, int>> p) {
    sort(p.begin(), p.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.first != b.first ? a.first < b.first : a.second > b.second; });
    vector<int> ys;
    for (auto& q : p) ys.push_back(q.second);
    return lis(ys);
}
int bruteChain(const vector<pair<int, int>>& p) {
    int n = p.size(), best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<pair<int, int>> s;
        for (int i = 0; i < n; i++) if (mask >> i & 1) s.push_back(p[i]);
        sort(s.begin(), s.end());
        bool ok = true;
        for (size_t i = 1; i < s.size(); i++) if (s[i].first <= s[i - 1].first || s[i].second <= s[i - 1].second) ok = false;
        if (ok) best = max(best, (int)s.size());
    }
    return best;
}
int main() {
    // P1: the envelopes (5, 4), (6, 4), (6, 7), (2, 3). P2: the pairs (1, 1), (2, 2), (2, 3), (3, 4). Brute: every subset. Method: sort, then LIS.
    vector<pair<int, int>> e = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    cout << "P1 brute=" << bruteChain(e) << " method=" << chain(e) << '\n';
    vector<pair<int, int>> f = {{1, 1}, {2, 2}, {2, 3}, {3, 4}};
    cout << "P2 brute=" << bruteChain(f) << " method=" << chain(f) << '\n';
    // N1: the longest chain of pairs (1, 2), (2, 3), (3, 4) where the next pair must start AFTER the previous one ends (b < a').
    vector<pair<int, int>> g = {{1, 2}, {2, 3}, {3, 4}};
    int best = 0;
    for (int mask = 0; mask < 8; mask++) {
        vector<pair<int, int>> s;
        for (int i = 0; i < 3; i++) if (mask >> i & 1) s.push_back(g[i]);
        bool ok = true;
        for (size_t i = 1; i < s.size(); i++) if (s[i].first <= s[i - 1].second) ok = false;
        if (ok) best = max(best, (int)s.size());
    }
    cout << "N1 brute=" << best << " method=" << chain(g) << '\n';
}
