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
// Theorem 6.4.2. lcp[r] = the longest common prefix of the suffixes of rank r - 1 and r (lcp[0] = 0), found here by comparing.
vector<int> lcpNaive(const string& s, const vector<int>& sa) {
    int n = s.size();
    vector<int> lcp(n, 0);
    for (int r = 1; r < n; r++)
        while (sa[r] + lcp[r] < n && sa[r - 1] + lcp[r] < n && s[sa[r] + lcp[r]] == s[sa[r - 1] + lcp[r]]) lcp[r]++;
    return lcp;
}
// The longest common prefix of the suffixes starting at a and b: the smallest lcp value between their ranks.
int lcpOfSuffixes(const vector<int>& lcp, const vector<int>& rank, int a, int b) {
    if (a == b) return (int)lcp.size() - a;
    int lo = min(rank[a], rank[b]) + 1, hi = max(rank[a], rank[b]);
    return *min_element(lcp.begin() + lo, lcp.begin() + hi + 1);
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

int direct(const string& s, int a, int b) {
    int h = 0;
    while (a + h < (int)s.size() && b + h < (int)s.size() && s[a + h] == s[b + h]) h++;
    return h;
}

int main() {
    string s = "banana";
    vector<int> sa = suffixArray(s), lcp = lcpNaive(s, sa), rank(s.size());
    for (int r = 0; r < (int)s.size(); r++) rank[sa[r]] = r;
    cout << "banana: lcp ="; for (int x : lcp) cout << " " << x; cout << "\n";
    cout << "lcp(1, 3) = " << lcpOfSuffixes(lcp, rank, 1, 3) << "\n";
    cout << "lcp(0, 5) = " << lcpOfSuffixes(lcp, rank, 0, 5) << "\n";
    cout << "lcp(2, 4) = " << lcpOfSuffixes(lcp, rank, 2, 4) << "\n";
    cout << "lcp(1, 5) = " << lcpOfSuffixes(lcp, rank, 1, 5) << "\n";
    // Check (not printed): for every string of length 1..10 over {a, b} and 1..6 over {a, b, c}, the minimum between the ranks
    // equals the common prefix found by comparing the two suffixes, for every pair of positions; and the suffixes that begin
    // with any given string form one stretch of ranks (part (c)).
    for (int sigma = 2; sigma <= 3; sigma++)
        for (const string& t : allStrings(sigma, sigma == 2 ? 10 : 6)) {
            int n = t.size();
            vector<int> sa2 = suffixArray(t), lcp2 = lcpNaive(t, sa2), rank2(n);
            for (int r = 0; r < n; r++) rank2[sa2[r]] = r;
            for (int a = 0; a < n; a++)
                for (int b = 0; b < n; b++)
                    if (lcpOfSuffixes(lcp2, rank2, a, b) != direct(t, a, b)) return 1;
            for (int len = 1; len <= n && len <= 3; len++)
                for (int i = 0; i + len <= n; i++) {
                    string p = t.substr(i, len);
                    int first = -1, last = -1, count = 0;
                    for (int r = 0; r < n; r++)
                        if (t.compare(sa2[r], len, p) == 0) {
                            if (first < 0) first = r;
                            last = r, count++;
                        }
                    if (last - first + 1 != count) return 1;
                }
        }
}
