#include <bits/stdc++.h>
using namespace std;

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
// Theorem 6.2.2. If s is a string repeated c >= 2 times, return the length of the repeated block; otherwise return 0.
// Uses prefixFunction (Theorem 6.2.3).
int repeatedBlockLength(const string& s) {
    int m = s.size();
    int q = m - prefixFunction(s)[m - 1];  // the smallest period (Theorem 6.2.1)
    return (q < m && m % q == 0) ? q : 0;
}
// snippet:end

int main() {
    for (string s : {"abcabc", "aaaa", "abcab", "ababab", "a", "abcd"}) {
        int q = repeatedBlockLength(s);
        cout << s << ": " << (q == 0 ? string("not a repetition") : "block " + s.substr(0, q) + " repeated " + to_string(s.size() / q) + " times") << "\n";
    }
    // Check (not printed): equal to trying every block length on every string of length 1..10 over {a, b}
    // and 1..7 over {a, b, c}.
    for (int sigma : {2, 3})
        for (int n = 1; n <= (sigma == 2 ? 10 : 7); n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= sigma;
            for (int code = 0; code < total; code++) {
                string s(n, 'a');
                for (int i = 0, c = code; i < n; i++, c /= sigma) s[i] = 'a' + c % sigma;
                int want = 0;
                for (int len = 1; len < n && !want; len++) {
                    if (n % len) continue;
                    bool ok = true;
                    for (int i = len; i < n; i++) ok = ok && s[i] == s[i - len];
                    if (ok) want = len;
                }
                if (repeatedBlockLength(s) != want) return 1;
            }
        }
}
