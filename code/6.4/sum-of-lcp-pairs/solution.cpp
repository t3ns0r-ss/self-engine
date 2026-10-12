#include <bits/stdc++.h>
using namespace std;

/*
Problem: the sum of the longest common prefixes of the suffixes starting at i and j, over all pairs i < j of positions.
Input: the string (lower-case letters, length up to 10^6).
Output: the sum (it needs 64 bits).
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
// By Theorem 6.4.2 the sum over pairs of suffixes is the sum, over all stretches lcp[l..r] (1 <= l <= r < n), of the stretch minimum.
// cur = the sum of the minimums of the stretches that end at r; the stack keeps (value, number of left ends with that minimum).
// Uses suffixArray and lcpArray.
long long sumOfLcp(const string& s) {
    int n = s.size();
    vector<int> sa = suffixArray(s), lcp = lcpArray(s, sa);
    vector<pair<int, long long>> stack;
    long long cur = 0, total = 0;
    for (int r = 1; r < n; r++) {
        long long ends = 1;
        while (!stack.empty() && stack.back().first >= lcp[r]) {
            cur -= (long long)stack.back().first * stack.back().second;
            ends += stack.back().second;
            stack.pop_back();
        }
        stack.push_back({lcp[r], ends});
        cur += (long long)lcp[r] * ends;
        total += cur;
    }
    return total;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << sumOfLcp(s) << "\n";
}
