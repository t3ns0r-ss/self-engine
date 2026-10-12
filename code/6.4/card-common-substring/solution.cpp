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
        string a = "xabcdy", b = "zbcdw";
        int best = 0;
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++) {
                int h = 0;
                while (i + h < a.size() && j + h < b.size() && a[i + h] == b[j + h]) h++;
                best = max(best, h);
            }
        string t = a + '#' + b;
        vector<int> sa = suffixArray(t), lcp = lcpArray(t, sa);
        int method = 0, na = a.size();
        for (size_t r = 1; r < t.size(); r++)
            if ((sa[r - 1] < na) != (sa[r] < na)) method = max(method, lcp[r]);
        cout << "P1 brute=" << best << " method=" << method << "\n";
    }
    {
        string s = "banana";
        int n = s.size();
        long long brute = 0, method = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int h = 0;
                while (j + h < n && s[i + h] == s[j + h]) h++;
                brute += h;
            }
        vector<int> sa = suffixArray(s), lcp = lcpArray(s, sa), rank(n);
        for (int r = 0; r < n; r++) rank[sa[r]] = r;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int lo = min(rank[i], rank[j]) + 1, hi = max(rank[i], rank[j]);
                method += *min_element(lcp.begin() + lo, lcp.begin() + hi + 1);
            }
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    {
        // N1: the question asks for the longest common subsequence, not substring, of two strings.
        string a = "abc", b = "acb";
        vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, 0));
        for (size_t i = 1; i <= a.size(); i++)
            for (size_t j = 1; j <= b.size(); j++)
                dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
        string t = a + '#' + b;
        vector<int> sa = suffixArray(t), lcp = lcpArray(t, sa);
        int method = 0, na = a.size();
        for (size_t r = 1; r < t.size(); r++)
            if ((sa[r - 1] < na) != (sa[r] < na)) method = max(method, lcp[r]);
        cout << "N1 brute=" << dp[a.size()][b.size()] << " method=" << method << "\n";
    }
}
