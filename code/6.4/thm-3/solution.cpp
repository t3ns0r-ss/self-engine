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

// snippet:begin
// Theorem 6.4.3 (Kasai). The array lcp in O(n): h is the common prefix length of suffix i with its predecessor in sorted order.
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
// snippet:end

// Every string of length 1..maxLen over the first sigma letters.
vector<string> allStrings(int sigma, int maxLen) {
    vector<string> out;
    for (int len = 1; len <= maxLen; len++) {
        long long total = 1;
        for (int i = 0; i < len; i++) total *= sigma;
        for (long long code = 0; code < total; code++) {
            string s(len, 'a');
            long long c = code;
            for (int i = 0; i < len; i++) s[i] = 'a' + c % sigma, c /= sigma;
            out.push_back(s);
        }
    }
    return out;
}

vector<int> lcpNaive(const string& s, const vector<int>& sa) {
    int n = s.size();
    vector<int> lcp(n, 0);
    for (int r = 1; r < n; r++)
        while (sa[r] + lcp[r] < n && sa[r - 1] + lcp[r] < n && s[sa[r] + lcp[r]] == s[sa[r - 1] + lcp[r]]) lcp[r]++;
    return lcp;
}

int main() {
    for (string s : {"banana", "aaaa", "abab"}) {
        cout << s << ": lcp =";
        for (int x : lcpArray(s, suffixArray(s))) cout << " " << x;
        cout << "\n";
    }
    // Check (not printed): the same as comparing neighbours directly, for every string of length 1..10 over {a, b} and
    // 1..6 over {a, b, c}.
    for (int sigma = 2; sigma <= 3; sigma++)
        for (const string& t : allStrings(sigma, sigma == 2 ? 10 : 6)) {
            vector<int> sa = suffixArray(t);
            if (lcpArray(t, sa) != lcpNaive(t, sa)) return 1;
        }
}
