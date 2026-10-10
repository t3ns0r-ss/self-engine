/*
Problem: is t a subsequence of s (can t be obtained by deleting characters of s)?
Input: two lines, s and t (non-empty, lowercase letters).
Output: YES or NO.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.6. Is t a subsequence of s? Match each character of t at its earliest position.
bool isSubsequence(const string& s, const string& t) {
    size_t j = 0;  // t[0..j-1] is matched
    for (char c : s)
        if (j < t.size() && c == t[j]) j++;
    return j == t.size();
}
// snippet:end

int main() {
    string s, t;
    cin >> s >> t;
    cout << (isSubsequence(s, t) ? "YES" : "NO") << "\n";
}
