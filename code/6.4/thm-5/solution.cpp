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
// Theorem 6.4.5. The suffixes that begin with p form the ranks [first, last): found by two binary searches, each step
// comparing p with the first |p| letters of a suffix. The occurrences of p are the starts sa[first], ..., sa[last - 1].
pair<int, int> occurrenceBlock(const string& s, const vector<int>& sa, const string& p) {
    int n = s.size(), m = p.size();
    auto cmp = [&](int start) { return s.compare(start, m, p); };  // < 0: below p, 0: begins with p, > 0: above p
    int lo = 0, hi = n;
    while (lo < hi) {  // the first rank that is not below p
        int mid = (lo + hi) / 2;
        if (cmp(sa[mid]) < 0) lo = mid + 1; else hi = mid;
    }
    int first = lo;
    hi = n;
    while (lo < hi) {  // the first rank that is above p
        int mid = (lo + hi) / 2;
        if (cmp(sa[mid]) <= 0) lo = mid + 1; else hi = mid;
    }
    return {first, lo};
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
    string s = "banana";
    vector<int> sa = suffixArray(s);
    for (string p : {"ana", "na", "an", "x", "banana", "a"}) {
        auto [first, last] = occurrenceBlock(s, sa, p);
        cout << p << ": ranks [" << first << ", " << last << "), count " << last - first << ", starts";
        vector<int> starts(sa.begin() + first, sa.begin() + last);
        for (int x : starts) cout << " " << x;
        cout << "\n";
    }
    // Check (not printed): the block holds exactly the starts found by scanning the text, for every string of length 1..9 over
    // {a, b} and every pattern of length 1..4 over {a, b, c}.
    for (const string& t : allStrings(2, 9)) {
        vector<int> sa2 = suffixArray(t);
        for (const string& p : allStrings(3, 4)) {
            auto [first, last] = occurrenceBlock(t, sa2, p);
            vector<int> got(sa2.begin() + first, sa2.begin() + last), want;
            for (int i = 0; i + p.size() <= t.size(); i++)
                if (t.compare(i, p.size(), p) == 0) want.push_back(i);
            sort(got.begin(), got.end());
            if (got != want) return 1;
        }
    }
}
