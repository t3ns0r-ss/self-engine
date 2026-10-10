/*
Problem: split a string into maximal blocks of equal characters. Print the number of blocks,
the length of the longest block, and the number of substrings made of a single repeated character.
Input: a string s (1 <= |s| <= 10^6) of lowercase letters.
Output: three numbers.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.2.4. Splits s into maximal blocks of equal characters: {number of blocks, longest block,
// number of substrings made of one repeated character}. j only moves forward, so the loops cost O(n) in all.
array<long long, 3> runStats(const string& s) {
    int n = s.size(), i = 0;
    long long blocks = 0, longest = 0, single = 0;
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;
        long long len = j - i;       // the block is s[i..j-1]
        blocks++;
        longest = max(longest, len);
        single += len * (len + 1) / 2;  // substrings inside one block (Theorem 0.2.3)
        i = j;                          // the next block starts where this one ended
    }
    return {blocks, longest, single};
}
// snippet:end

int main() {
    string s;
    cin >> s;
    array<long long, 3> r = runStats(s);
    cout << r[0] << " " << r[1] << " " << r[2] << "\n";
}
