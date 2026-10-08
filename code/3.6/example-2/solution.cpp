/*
Problem: LeetCode 132 Palindrome Partitioning II, as a program. Cut a string into pieces that are all
palindromes, using as few cuts as possible.
Input: a string s of lowercase letters (1 <= |s| <= 2000).
Output: the minimum number of cuts.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    // pal[l][r]: is s[l..r] a palindrome? Shorter segments inside are ready when l runs downwards.
    vector<vector<char>> pal(n, vector<char>(n, 0));
    for (int l = n - 1; l >= 0; l--)
        for (int r = l; r < n; r++)
            pal[l][r] = (s[l] == s[r]) && (r - l < 2 || pal[l + 1][r - 1]);
    // pieces[i] = fewest palindromes that cover the prefix s[0..i-1]; the last piece is s[j..i-1]
    vector<int> pieces(n + 1, INT_MAX);
    pieces[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            if (pal[j][i - 1] && pieces[j] + 1 < pieces[i]) pieces[i] = pieces[j] + 1;
    cout << pieces[n] - 1 << "\n";  // k pieces need k - 1 cuts
}
