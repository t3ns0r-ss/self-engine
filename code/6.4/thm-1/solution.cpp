#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.4.1. The suffix array by doubling: after the round with step k, rnk orders the suffixes by their first 2k letters.
// key(i) = (the rank of the block s[i..i+k), the rank of the block s[i+k..i+2k)), and -1 if the second block is empty.
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
vector<int> bruteSuffixArray(const string& s) {
    vector<int> sa(s.size());
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&](int a, int b) { return s.substr(a) < s.substr(b); });
    return sa;
}

int main() {
    for (string s : {"banana", "aaaa", "abab"}) {
        cout << s << ": sa =";
        for (int x : suffixArray(s)) cout << " " << x;
        cout << "\n";
    }
    // Check (not printed): the same as sorting the suffixes as strings, for every string of length 1..10 over {a, b}
    // and every string of length 1..6 over {a, b, c}.
    for (const string& s : allStrings(2, 10)) if (suffixArray(s) != bruteSuffixArray(s)) return 1;
    for (const string& s : allStrings(3, 6)) if (suffixArray(s) != bruteSuffixArray(s)) return 1;
}
