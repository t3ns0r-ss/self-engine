/*
Problem: the length of the longest strictly increasing subsequence (t = 0) or of the longest non-decreasing
subsequence (t = 1) of an array.
Input: n t (1 <= n <= 2 * 10^5, t in {0, 1}), then n integers (|a_i| <= 10^9).
Output: the length.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.2. tails[k] = the smallest last value of a valid subsequence of length k + 1 so far. strict: replace the first
// tail >= x (lower_bound); non-strict: the first tail > x (upper_bound).
int lisLength(const vector<int>& a, bool strict) {
    vector<int> tails;
    for (int x : a) {
        auto it = strict ? lower_bound(tails.begin(), tails.end(), x) : upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);  // x extends the longest subsequence
        else *it = x;                               // x is a smaller ending for that length
    }
    return tails.size();
}
// snippet:end

int main() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << lisLength(a, t == 0) << "\n";
}
