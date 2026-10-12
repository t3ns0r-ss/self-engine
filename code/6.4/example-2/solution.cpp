#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 2102, Finding Patterns. Given a string and k patterns, check for each pattern whether it appears in the string.
Input: the string (up to 10^5 letters), k (up to 5·10^5), then the k patterns (total length up to 5·10^5).
Output: YES or NO for each pattern.
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
// Theorem 6.4.5: the first suffix in sorted order that is not below p begins with p exactly when p occurs. One binary search
// per pattern, each step comparing p with the first |p| letters of a suffix. Uses suffixArray (Theorem 6.4.1).
bool occurs(const string& s, const vector<int>& sa, const string& p) {
    int lo = 0, hi = s.size();
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (s.compare(sa[mid], p.size(), p) < 0) lo = mid + 1; else hi = mid;
    }
    return lo < (int)s.size() && s.compare(sa[lo], p.size(), p) == 0;
}
// snippet:end

int main() {
    string s;
    int k;
    cin >> s >> k;
    vector<int> sa = suffixArray(s);
    while (k--) {
        string p;
        cin >> p;
        cout << (occurs(s, sa, p) ? "YES" : "NO") << "\n";
    }
}
