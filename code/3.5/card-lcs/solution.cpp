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
    // P1: the LCS of ACB and ABC. P2: the LCS of AGGTAB and GXTXAYB. Brute: every subsequence of the first. Method: the table.
    cout << "P1 brute=" << bruteLcs("ACB", "ABC") << " method=" << lcs("ACB", "ABC") << '\n';
    cout << "P2 brute=" << bruteLcs("AGGTAB", "GXTXAYB") << " method=" << lcs("AGGTAB", "GXTXAYB") << '\n';
    // N1: two permutations of 1..100000: the table has 10^10 cells; the answer is the LIS of the positions.
    int n = 100000;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    mt19937 rng(5);
    shuffle(p.begin(), p.end(), rng);
    long long cells = (long long)n * n;
    cout << "N1 brute=" << lis(p) << " method=" << (cells > 100000000LL ? "too-slow" : "ok") << '\n';
}
