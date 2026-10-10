#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.6. Is t a subsequence of s? Match each character of t at its earliest position.
bool isSubsequence(const string& s, const string& t) {
    size_t j = 0;  // t[0..j-1] is matched
    for (char c : s)
        if (j < t.size() && c == t[j]) j++;
    return j == t.size();
}
// snippet:end

int main() {
    cout << "ace in abcde: " << (isSubsequence("abcde", "ace") ? "yes" : "no") << '\n';
    cout << "aec in abcde: " << (isSubsequence("abcde", "aec") ? "yes" : "no") << '\n';
    cout << "(empty) in x: " << (isSubsequence("x", "") ? "yes" : "no") << '\n';
    mt19937 rng(6);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 7, m = rng() % 4;
        string s, t;
        for (int i = 0; i < n; i++) s += char('a' + rng() % 3);
        for (int i = 0; i < m; i++) t += char('a' + rng() % 3);
        bool want = false;
        for (int mask = 0; mask < (1 << n); mask++) {
            string u;
            for (int i = 0; i < n; i++) if (mask >> i & 1) u += s[i];
            want |= u == t;
        }
        if (want != isSubsequence(s, t)) return 1;
    }
}
