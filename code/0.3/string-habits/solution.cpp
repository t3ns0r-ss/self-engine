/*
Problem: for a string s of letters, print three things.
1. The fewest letters to change so that s reads the same backwards.
2. The lengths of its runs (blocks of equal neighbouring letters), separated by spaces.
3. Yes if the letters at positions 0, 2, 4, ... are lowercase and those at positions 1, 3, 5, ... are uppercase, else No.
Input: s (1 <= |s| <= 1000, English letters).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Fewest letter changes that make s a palindrome: compare the letters at both ends, moving inwards.
int changesToPalindrome(const string& s) {
    int changes = 0;
    for (int i = 0, j = (int)s.size() - 1; i < j; i++, j--)
        if (s[i] != s[j]) changes++;
    return changes;
}

// Lengths of the runs of s, one scan.
vector<int> runLengths(const string& s) {
    vector<int> runs;
    for (int i = 0; i < (int)s.size(); i++) {
        if (i > 0 && s[i] == s[i - 1]) runs.back()++;  // the same run goes on
        else runs.push_back(1);                          // a new run starts here
    }
    return runs;
}

// Lowercase at even positions, uppercase at odd positions?
bool lowerUpperAlternate(const string& s) {
    for (int i = 0; i < (int)s.size(); i++) {
        bool right = (i % 2 == 0) ? islower((unsigned char)s[i]) : isupper((unsigned char)s[i]);
        if (!right) return false;
    }
    return true;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << changesToPalindrome(s) << "\n";
    vector<int> runs = runLengths(s);
    for (size_t i = 0; i < runs.size(); i++) cout << runs[i] << (i + 1 < runs.size() ? " " : "\n");
    cout << (lowerUpperAlternate(s) ? "Yes" : "No") << "\n";
}
