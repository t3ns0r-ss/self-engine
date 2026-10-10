/*
Problem: AtCoder ABC 329 C Count xxx. Count the different strings that are non-empty substrings of S
made of one repeated character.
Input: N (<= 2*10^5), then S of lowercase letters.
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Different strings made of one repeated letter: for each letter c, the strings c, cc, ..., c^L occur,
// where L is the longest block of c.
long long countRepeated(const string& s) {
    int n = s.size(), i = 0;
    vector<int> longest(26, 0);
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;  // the block s[i..j-1]; j only moves forward
        longest[s[i] - 'a'] = max(longest[s[i] - 'a'], j - i);
        i = j;
    }
    long long total = 0;
    for (int c = 0; c < 26; c++) total += longest[c];
    return total;
}
// snippet:end

int main() {
    int n;
    string s;
    cin >> n >> s;
    cout << countRepeated(s) << "\n";
}
