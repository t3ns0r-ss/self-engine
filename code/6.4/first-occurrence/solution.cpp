#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 2103 and 2104 style. A text and q patterns. For each pattern print the number of its occurrences in the text
(occurrences may overlap) and the position of the first one (counting from 1), or 0 and -1 if there is none.
Input: the text, q, then the q patterns (lower-case letters; the text has up to 10^5 letters, the patterns up to 5·10^5 in all).
Output: for each pattern, the count and the first position.
*/

vector<int> suffixArray(const string& s) {
    int n = s.size(), m = max(n, 256) + 1;
    vector<int> sa(n), rk(n), tmp(n), second(n), cnt(m);
    for (int i = 0; i < n; i++) rk[i] = (unsigned char)s[i], cnt[rk[i]]++;
    for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[i]]] = i;
    for (int k = 1;; k *= 2) {
        int p = 0;
        for (int i = n - k; i < n; i++) second[p++] = i;  // the empty second block is the smallest key
        for (int j = 0; j < n; j++)
            if (sa[j] >= k) second[p++] = sa[j] - k;       // in the order of the second block
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) cnt[rk[i]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int j = n - 1; j >= 0; j--) sa[--cnt[rk[second[j]]]] = second[j];  // stable sort by the first block
        auto key = [&](int i) { return pair<int, int>(rk[i], i + k < n ? rk[i + k] : -1); };
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + (key(sa[i - 1]) < key(sa[i]));
        rk = tmp;
        if (rk[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

vector<int> lcpArray(const string& s, const vector<int>& sa) {  // lcp[r] = lcp of the suffixes of rank r - 1 and r, lcp[0] = 0
    int n = s.size();
    vector<int> rank(n), lcp(n, 0);
    for (int r = 0; r < n; r++) rank[sa[r]] = r;
    for (int i = 0, h = 0; i < n; i++) {
        if (rank[i] == 0) { h = 0; continue; }
        int j = sa[rank[i] - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        lcp[rank[i]] = h;
        if (h > 0) h--;  // the next suffix shares at least h - 1 letters with its predecessor
    }
    return lcp;
}

// snippet:begin
// Theorem 6.4.5 and a range minimum (topic 5.1): the occurrences of p are the starts sa[first .. last); their number is the
// size of the block and the first occurrence is the smallest start in the block. mn[j][r] = the smallest start among the
// ranks r, ..., r + 2^j - 1. Uses suffixArray (Theorem 6.4.1).
struct Occurrences {
    string s;
    vector<int> sa;
    vector<vector<int>> mn;
    Occurrences(const string& text) : s(text), sa(suffixArray(text)) {
        int n = s.size();
        mn.push_back(sa);
        for (int j = 1; (1 << j) <= n; j++) {
            mn.push_back(vector<int>(n - (1 << j) + 1));
            for (int r = 0; r + (1 << j) <= n; r++) mn[j][r] = min(mn[j - 1][r], mn[j - 1][r + (1 << (j - 1))]);
        }
    }
    int lowerBound(const string& p, bool above) const {  // the first rank that is not below p (or, if above, that is above p)
        int lo = 0, hi = s.size();
        while (lo < hi) {
            int mid = (lo + hi) / 2, c = s.compare(sa[mid], p.size(), p);
            if (c < 0 || (above && c == 0)) lo = mid + 1; else hi = mid;
        }
        return lo;
    }
    pair<int, int> query(const string& p) const {  // {count, first start from 0, or -1}
        int lo = lowerBound(p, false), hi = lowerBound(p, true);
        if (lo == hi) return {0, -1};
        int j = 31 - __builtin_clz(hi - lo);
        return {hi - lo, min(mn[j][lo], mn[j][hi - (1 << j)])};
    }
};
// snippet:end

int main() {
    string text;
    int q;
    cin >> text >> q;
    Occurrences occ(text);
    while (q--) {
        string p;
        cin >> p;
        auto [count, first] = occ.query(p);
        cout << count << " " << (first < 0 ? -1 : first + 1) << "\n";
    }
}
