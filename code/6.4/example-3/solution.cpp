#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 3225, Inverse Suffix Array. Given a permutation of 1..n, find a string of lower-case letters whose suffix array is this
permutation, or print -1 if there is none. (Any string is accepted; this program prints the smallest one in letters used.)
Input: n (up to 10^5), then the permutation.
Output: the string or -1.
*/

// snippet:begin
// For neighbours A = sa[r - 1] and B = sa[r] in sorted order, the letters satisfy s[A] <= s[B]; equal letters are possible only if the
// rest after A is below the rest after B (the empty rest is the smallest). Use equal letters whenever that is possible, and
// the next letter otherwise. If more than 26 letters are needed, no string has this suffix array.
string inverseSuffixArray(const vector<int>& sa) {
    int n = sa.size(), letter = 0;
    vector<int> rank(n + 1, -1);
    for (int r = 0; r < n; r++) rank[sa[r]] = r;
    string s(n, 'a');
    for (int r = 1; r < n; r++) {
        if (rank[sa[r - 1] + 1] > rank[sa[r] + 1]) letter++;
        if (letter >= 26) return "-1";
        s[sa[r]] = 'a' + letter;
    }
    return s;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> sa(n);
    for (int& x : sa) cin >> x, x--;
    cout << inverseSuffixArray(sa) << "\n";
}
