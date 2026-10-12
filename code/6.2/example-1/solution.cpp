#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1753 String Matching. Given a string (the text) and a pattern, count the places where the pattern occurs
in the text.
Input: the text, then the pattern (lower-case letters, lengths up to 10^6).
Output: the number of occurrences.
*/

vector<int> prefixFunction(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    return pi;
}

// snippet:begin
// The number of occurrences of the pattern in the text: the prefix function of pattern + '#' + text, and a count of the
// places where it equals the length of the pattern (Theorem 6.2.4 (a)). Uses prefixFunction.
long long countMatches(const string& text, const string& pattern) {
    string w = pattern + '#' + text;
    vector<int> pi = prefixFunction(w);
    long long count = 0;
    for (int value : pi) count += value == (int)pattern.size();
    return count;
}
// snippet:end

int main() {
    string text, pattern;
    cin >> text >> pattern;
    cout << countMatches(text, pattern) << "\n";
}
