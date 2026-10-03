/*
Problem: split a string into maximal blocks of equal characters. Print the number of blocks,
the length of the longest block, and the number of substrings made of a single repeated character.
Input: a string s (1 <= |s| <= 10^6) of lowercase letters.
Output: three numbers.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    int blocks = 0, longest = 0;
    long long single = 0;  // up to n(n+1)/2, about 5*10^11
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;  // j only moves forward: O(n) in total (Theorem 0.2.4)
        long long len = j - i;              // the block is s[i..j-1]
        blocks++;
        longest = max(longest, (int)len);
        single += len * (len + 1) / 2;      // substrings inside one block (Theorem 0.2.3)
        i = j;                              // the next block starts where this one ended
    }
    cout << blocks << " " << longest << " " << single << "\n";
}
