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
int main() {
    // P1: the LIS of 3 1 4 1 5 9 2 6. Brute: every subsequence. Method: the tails array.
    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "P1 brute=" << bruteLis(a) << " method=" << lis(a) << '\n';
    // N1: the longest contiguous increasing run of 1 3 2 4 5, computed as the LIS.
    vector<int> b = {1, 3, 2, 4, 5};
    int run = 1, best = 1;
    for (size_t i = 1; i < b.size(); i++) { run = b[i] > b[i - 1] ? run + 1 : 1; best = max(best, run); }
    cout << "N1 brute=" << best << " method=" << lis(b) << '\n';
    // N2: the longest strictly increasing sequence after reordering 3 1 4 1 5 freely (the distinct values), computed as the LIS.
    vector<int> c = {3, 1, 4, 1, 5};
    cout << "N2 brute=" << set<int>(c.begin(), c.end()).size() << " method=" << lis(c) << '\n';
}
