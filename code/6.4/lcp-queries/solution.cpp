#include <bits/stdc++.h>
using namespace std;

/*
Problem: a string and q queries (a, b); for each, the longest common prefix of the suffixes starting at positions a and b (from 0).
Input: the string (up to 10^6 letters), q, then the q pairs.
Output: the answers, one per line.
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
// Theorem 6.4.2: the answer is the minimum of lcp over the ranks after the smaller rank up to the larger rank, taken in O(1)
// from a sparse table (topic 5.1). Uses suffixArray and lcpArray.
struct LcpQueries {
    int n;
    vector<int> rank;
    vector<vector<int>> table;  // table[j][r] = min of lcp[r .. r + 2^j - 1]
    LcpQueries(const string& s) : n(s.size()), rank(s.size()) {
        vector<int> sa = suffixArray(s);
        table.push_back(lcpArray(s, sa));
        for (int r = 0; r < n; r++) rank[sa[r]] = r;
        for (int j = 1; (1 << j) <= n; j++) {
            table.push_back(vector<int>(n - (1 << j) + 1));
            for (int r = 0; r + (1 << j) <= n; r++) table[j][r] = min(table[j - 1][r], table[j - 1][r + (1 << (j - 1))]);
        }
    }
    int lcp(int a, int b) const {
        if (a == b) return n - a;
        int lo = min(rank[a], rank[b]) + 1, hi = max(rank[a], rank[b]) + 1;  // the stretch lcp[lo .. hi - 1]
        int j = 31 - __builtin_clz(hi - lo);
        return min(table[j][lo], table[j][hi - (1 << j)]);
    }
};
// snippet:end

int main() {
    string s;
    int q;
    cin >> s >> q;
    LcpQueries lq(s);
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lq.lcp(a, b) << "\n";
    }
}
