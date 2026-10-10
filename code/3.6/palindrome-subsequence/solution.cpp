/*
Problem: the length of the longest palindromic subsequence of a string.
Input: a string s of lowercase letters (1 <= |s| <= 5000).
Output: the length.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.6.4. Row l of P[l][r]; l runs downwards, so row l + 1 is ready.
int longestPalindromicSubsequence(const string& s) {
    int n = s.size();
    vector<int> next(n, 0), cur(n, 0);
    for (int l = n - 1; l >= 0; l--) {
        cur[l] = 1;  // one letter
        for (int r = l + 1; r < n; r++) {
            if (s[l] == s[r]) cur[r] = (l + 1 <= r - 1 ? next[r - 1] : 0) + 2;  // both ends used
            else cur[r] = max(next[r], cur[r - 1]);                            // drop one end
        }
        swap(next, cur);
    }
    return next[n - 1];
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << longestPalindromicSubsequence(s) << "\n";
}
