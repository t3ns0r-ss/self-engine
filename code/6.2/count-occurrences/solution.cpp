#include <bits/stdc++.h>
using namespace std;

/*
Problem: count the places where the pattern t occurs in the text s (occurrences may overlap).
Input: s, then t (lower-case letters, lengths up to 10^6).
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
// The number of occurrences of t in s in O(|s| + |t|), reading the text once and keeping k = the number of letters of t
// matched at the end of the text read so far (the state of the matching automaton, Theorem 6.2.4).
// Uses prefixFunction (Theorem 6.2.3).
long long countOccurrences(const string& s, const string& t) {
    int m = t.size();
    vector<int> pi = prefixFunction(t);
    long long count = 0;
    int k = 0;
    for (char c : s) {
        while (k > 0 && (k == m || t[k] != c)) k = pi[k - 1];  // after a full match, or on a mismatch: fall back
        if (t[k] == c) k++;
        if (k == m) count++;
    }
    return count;
}
// snippet:end

int main() {
    string s, t;
    cin >> s >> t;
    cout << countOccurrences(s, t) << "\n";
}
