/*
Problem: find one longest strictly increasing (t = 0) or non-decreasing (t = 1) subsequence of an array, not only its length.
Input: n t (1 <= n <= 2 * 10^5, t in {0, 1}), then n integers (|a_i| <= 10^9).
Output: the length of the subsequence found, then 1 if the subsequence found is valid (positions increase and the values obey
the rule) and has the longest possible length (the length of the tails array), otherwise 0.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.2 with parents. tailIdx[k] = the index of the element that ends the best subsequence of length k + 1, and
// parent[i] = the index before i in the subsequence that ends at i. Returns the indices of one longest subsequence.
vector<int> lisRecover(const vector<int>& a, bool strict) {
    int n = a.size();
    vector<int> tailIdx, parent(n, -1);
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = tailIdx.size();  // first k whose tail cannot be followed by a[i]
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            bool canFollow = strict ? a[tailIdx[mid]] < a[i] : a[tailIdx[mid]] <= a[i];
            if (canFollow) lo = mid + 1;
            else hi = mid;
        }
        parent[i] = lo > 0 ? tailIdx[lo - 1] : -1;
        if (lo == (int)tailIdx.size()) tailIdx.push_back(i);
        else tailIdx[lo] = i;
    }
    vector<int> result;
    for (int i = tailIdx.back(); i != -1; i = parent[i]) result.push_back(i);
    reverse(result.begin(), result.end());
    return result;
}
// snippet:end

int lisLength(const vector<int>& a, bool strict) {
    vector<int> tails;
    for (int x : a) {
        auto it = strict ? lower_bound(tails.begin(), tails.end(), x) : upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}

int main() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<int> idx = lisRecover(a, t == 0);
    bool ok = (int)idx.size() == lisLength(a, t == 0);
    for (size_t k = 1; k < idx.size(); k++) {
        if (idx[k] <= idx[k - 1]) ok = false;
        if (t == 0 ? a[idx[k]] <= a[idx[k - 1]] : a[idx[k]] < a[idx[k - 1]]) ok = false;
    }
    cout << idx.size() << " " << (ok ? 1 : 0) << "\n";
}
