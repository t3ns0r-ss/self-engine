#include <bits/stdc++.h>
using namespace std;

vector<int> suffixArray(const string& s) {
    int n = s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; i++) rnk[i] = (unsigned char)s[i];
    for (int k = 1;; k *= 2) {
        auto key = [&](int i) { return pair<int, int>(rnk[i], i + k < n ? rnk[i + k] : -1); };
        sort(sa.begin(), sa.end(), [&](int a, int b) { return key(a) < key(b); });
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + (key(sa[i - 1]) < key(sa[i]));
        rnk = tmp;
        if (rnk[sa[n - 1]] == n - 1) break;
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

pair<int, int> block(const string& s, const vector<int>& sa, const string& p) {
    int n = s.size(), m = p.size();
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (s.compare(sa[mid], m, p) < 0) lo = mid + 1; else hi = mid;
    }
    int first = lo;
    hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (s.compare(sa[mid], m, p) <= 0) lo = mid + 1; else hi = mid;
    }
    return {first, lo};
}

int main() {
    {
        string s = "banana", p = "ana";
        int brute = 0;
        for (size_t i = 0; i + p.size() <= s.size(); i++) brute += s.compare(i, p.size(), p) == 0;
        auto [first, last] = block(s, suffixArray(s), p);
        cout << "P1 brute=" << brute << " method=" << last - first << "\n";
    }
    {
        string s = "aaaaa", p = "aa";
        int brute = 0;
        for (size_t i = 0; i + p.size() <= s.size(); i++) brute += s.compare(i, p.size(), p) == 0;
        auto [first, last] = block(s, suffixArray(s), p);
        cout << "P2 brute=" << brute << " method=" << last - first << "\n";
    }
    {
        // N1: the pattern has a wildcard ? that matches any letter; the block of the suffix array treats ? as a letter.
        string s = "abcb", p = "a?c";
        int brute = 0;
        for (size_t i = 0; i + p.size() <= s.size(); i++) {
            bool ok = true;
            for (size_t j = 0; j < p.size(); j++) ok = ok && (p[j] == '?' || p[j] == s[i + j]);
            brute += ok;
        }
        auto [first, last] = block(s, suffixArray(s), p);
        cout << "N1 brute=" << brute << " method=" << last - first << "\n";
    }
}
