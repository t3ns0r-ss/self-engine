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
    // P1: cat -> cut. Brute: breadth-first search over strings by single edits.
    map<string, int> dist;
    queue<string> q;
    dist["cat"] = 0, q.push("cat");
    while (!q.empty()) {
        string s = q.front();
        q.pop();
        if (dist[s] >= 3) continue;
        vector<string> next;
        for (size_t i = 0; i <= s.size(); i++) for (char c : string("acut")) next.push_back(s.substr(0, i) + c + s.substr(i));
        for (size_t i = 0; i < s.size(); i++) {
            next.push_back(s.substr(0, i) + s.substr(i + 1));
            for (char c : string("acut")) next.push_back(s.substr(0, i) + c + s.substr(i + 1));
        }
        for (auto& u : next) if (!dist.count(u)) dist[u] = dist[s] + 1, q.push(u);
    }
    cout << "P1 brute=" << dist["cut"] << " method=" << editDistance("cat", "cut") << '\n';
    // N1: only deletions are allowed on both strings, "a" and "b": 2 deletions; the edit distance allows a replacement.
    cout << "N1 brute=" << 1 + 1 << " method=" << editDistance("a", "b") << '\n';
    // N2: only replacements allowed on equal-length strings abc and bca: the differing positions; the edit distance uses a deletion and an insertion.
    int diff = 0;
    string x = "abc", y = "bca";
    for (int i = 0; i < 3; i++) diff += x[i] != y[i];
    cout << "N2 brute=" << diff << " method=" << editDistance(x, y) << '\n';
}
