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

int main() {
    {
        string s = "aabaaa";
        int n = s.size();
        string brute = s;
        for (int i = 1; i < n; i++) brute = min(brute, s.substr(i) + s.substr(0, i));
        string method;
        for (int start : suffixArray(s + s))
            if (start < n) { method = s.substr(start) + s.substr(0, start); break; }
        cout << "P1 brute=" << brute << " method=" << method << "\n";
    }
    {
        string s = "abab";
        int n = s.size();
        string brute;
        for (int i = 0; i < n; i++)
            for (int len = 1; i + len <= n; len++) brute = max(brute, s.substr(i, len));
        vector<int> sa = suffixArray(s);
        string method = s.substr(sa[n - 1]);  // the largest substring is the last suffix in sorted order
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    {
        // N1: the question asks for the smallest subsequence of length 2, not for a suffix.
        string s = "bca";
        int n = s.size();
        string brute = "zz";
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) brute = min(brute, string() + s[i] + s[j]);
        vector<int> sa = suffixArray(s);
        string method;
        for (int r = 0; r < n; r++)
            if (n - sa[r] >= 2) { method = s.substr(sa[r], 2); break; }
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
