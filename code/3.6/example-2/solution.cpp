/*
Problem: LeetCode 132 Palindrome Partitioning II, as a program. Cut a string into pieces that are all
palindromes, using as few cuts as possible.
Input: a string s of lowercase letters (1 <= |s| <= 2000).
Output: the minimum number of cuts.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// LeetCode 132. pal[l][r]: is s[l..r] a palindrome (l runs downwards so the inner segment is ready); pieces[i] = the fewest
// palindromes covering the prefix of length i, with the last piece s[j..i-1]. The cuts are pieces - 1.
int minCuts(const string& s) {
    int n = s.size();
    vector<vector<char>> pal(n, vector<char>(n, 0));
    for (int l = n - 1; l >= 0; l--)
        for (int r = l; r < n; r++) pal[l][r] = (s[l] == s[r]) && (r - l < 2 || pal[l + 1][r - 1]);
    vector<int> pieces(n + 1, INT_MAX);
    pieces[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            if (pal[j][i - 1] && pieces[j] + 1 < pieces[i]) pieces[i] = pieces[j] + 1;
    return pieces[n] - 1;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << minCuts(s) << "\n";
}
