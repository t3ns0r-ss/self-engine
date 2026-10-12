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
        string s = "banana";
        int n = s.size();
        set<string> all;
        for (int i = 0; i < n; i++)
            for (int len = 1; i + len <= n; len++) all.insert(s.substr(i, len));
        vector<int> sa = suffixArray(s), lcp = lcpArray(s, sa);
        long long method = (long long)n * (n + 1) / 2;
        for (int r = 1; r < n; r++) method -= lcp[r];
        cout << "P1 brute=" << all.size() << " method=" << method << "\n";
    }
    {
        string s = "banana";
        int n = s.size(), k = 3;
        set<string> all;
        for (int i = 0; i + k <= n; i++) all.insert(s.substr(i, k));
        vector<int> sa = suffixArray(s), lcp = lcpArray(s, sa);
        int method = 0;  // suffixes of length at least k, minus those that share k letters with the previous suffix
        for (int r = 0; r < n; r++) method += n - sa[r] >= k;
        for (int r = 1; r < n; r++) method -= lcp[r] >= k;
        cout << "P2 brute=" << all.size() << " method=" << method << "\n";
    }
    {
        // N1: the question asks for different subsequences, not substrings.
        string s = "aba";
        int n = s.size();
        set<string> all;
        for (int mask = 1; mask < (1 << n); mask++) {
            string t;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) t += s[i];
            all.insert(t);
        }
        vector<int> sa = suffixArray(s), lcp = lcpArray(s, sa);
        long long method = (long long)n * (n + 1) / 2;
        for (int r = 1; r < n; r++) method -= lcp[r];
        cout << "N1 brute=" << all.size() << " method=" << method << "\n";
    }
}
