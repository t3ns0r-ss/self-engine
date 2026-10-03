/*
Problem: is t a subsequence of s (can t be obtained by deleting characters of s)?
Input: two lines, s and t (non-empty, lowercase letters).
Output: YES or NO.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    size_t j = 0;  // t[0..j-1] is matched
    for (char c : s) {
        if (j < t.size() && c == t[j]) j++;  // match t[j] at its earliest position
    }
    cout << (j == t.size() ? "YES" : "NO") << "\n";
}
