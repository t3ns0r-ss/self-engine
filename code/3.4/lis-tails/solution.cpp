/*
Problem: the length of the longest strictly increasing subsequence (t = 0) or of the longest non-decreasing
subsequence (t = 1) of an array.
Input: n t (1 <= n <= 2 * 10^5, t in {0, 1}), then n integers (|a_i| <= 10^9).
Output: the length.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;
    // tails[k] = smallest last value of a valid subsequence of length k + 1 so far (Theorem 3.4.2)
    vector<int> tails;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        // strict: replace the first tail >= x; non-strict: the first tail > x
        auto it = (t == 0) ? lower_bound(tails.begin(), tails.end(), x)
                           : upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);  // x extends the longest subsequence
        else *it = x;                               // x is a smaller ending for that length
    }
    cout << tails.size() << "\n";
}
