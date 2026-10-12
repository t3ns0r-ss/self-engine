#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 2110 style. For every k from 1 to n print the number of different substrings of length k.
Input: the string (lower-case letters, length up to 10^6).
Output: the n numbers on one line.
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
// For each length k: the suffixes of length at least k, minus those whose lcp with the previous suffix is at least k
// (Theorem 6.4.4). Both counts are made for all k at once with a difference array.
vector<long long> distinctByLength(const string& s) {
    int n = s.size();
    vector<int> sa = suffixArray(s), lcp = lcpArray(s, sa);
    vector<long long> diff(n + 2, 0);
    for (int r = 0; r < n; r++) diff[1]++, diff[n - sa[r] + 1]--;       // suffix r counts for k = 1 .. n - sa[r]
    for (int r = 1; r < n; r++) diff[1]--, diff[lcp[r] + 1]++;          // and is taken off for k = 1 .. lcp[r]
    vector<long long> count(n + 1, 0);
    for (int k = 1; k <= n; k++) count[k] = count[k - 1] + diff[k];
    return count;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    vector<long long> count = distinctByLength(s);
    for (size_t k = 1; k < count.size(); k++) cout << count[k] << (k + 1 < count.size() ? " " : "\n");
}
