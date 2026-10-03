/*
Problem: AtCoder ABC 329 C Count xxx. Count the different strings that are non-empty substrings of S
made of one repeated character.
Input: N (<= 2*10^5), then S of lowercase letters.
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    // For each letter c, the strings c, cc, ..., c^L all occur, where L is the longest block of c.
    vector<int> longest(26, 0);
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;  // the block s[i..j-1]; j only moves forward (Theorem 0.2.4)
        int c = s[i] - 'a';
        longest[c] = max(longest[c], j - i);
        i = j;
    }
    long long total = 0;
    for (int c = 0; c < 26; c++) total += longest[c];
    cout << total << "\n";
}
