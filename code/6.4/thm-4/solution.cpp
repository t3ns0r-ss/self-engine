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

// snippet:begin
// Theorem 6.4.4. The number of different substrings, and for each length k the number of different substrings of length k.
long long countDistinct(int n, const vector<int>& lcp) {
    long long total = (long long)n * (n + 1) / 2;
    for (int r = 1; r < n; r++) total -= lcp[r];
    return total;
}
vector<long long> distinctByLength(int n, const vector<int>& sa, const vector<int>& lcp) {
    vector<long long> count(n + 2, 0);  // count[k] = #{r : n - sa[r] >= k} - #{r : lcp[r] >= k}
    for (int r = 0; r < n; r++) count[1]++, count[n - sa[r] + 1]--;  // the suffix of rank r has length n - sa[r]
    for (int r = 1; r < n; r++) count[1]--, count[lcp[r] + 1]++;
    for (int k = 1; k <= n; k++) count[k] += count[k - 1];
    return count;
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

int main() {
    for (string s : {"banana", "aaaa", "abab"}) {
        int n = s.size();
        vector<int> sa = suffixArray(s), lcp = lcpArray(s, sa);
        cout << s << ": " << countDistinct(n, lcp) << " distinct; by length:";
        vector<long long> by = distinctByLength(n, sa, lcp);
        for (int k = 1; k <= n; k++) cout << " " << by[k];
        cout << "\n";
    }
    // Check (not printed): compared with collecting all substrings in a set, for every string of length 1..10 over {a, b}
    // and 1..6 over {a, b, c}.
    for (int sigma = 2; sigma <= 3; sigma++)
        for (const string& t : allStrings(sigma, sigma == 2 ? 10 : 6)) {
            int n = t.size();
            vector<int> sa = suffixArray(t), lcp = lcpArray(t, sa);
            vector<set<string>> sets(n + 1);
            for (int i = 0; i < n; i++)
                for (int len = 1; i + len <= n; len++) sets[len].insert(t.substr(i, len));
            long long all = 0;
            vector<long long> by = distinctByLength(n, sa, lcp);
            for (int k = 1; k <= n; k++) {
                all += sets[k].size();
                if ((long long)sets[k].size() != by[k]) return 1;
            }
            if (all != countDistinct(n, lcp)) return 1;
        }
}
