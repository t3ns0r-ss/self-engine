#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.2.3. The prefix function in O(n): pi[i] = the length of the longest border of s[0..i].
vector<int> prefixFunction(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int k = pi[i - 1];                               // a border of s[0..i-1]: try to extend it by s[i]
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];     // it cannot be extended: fall back to the next shorter border
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    return pi;
}
// snippet:end

vector<int> slow(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 0; i < n; i++)
        for (int k = i; k >= 1; k--)
            if (s.compare(0, k, s, i + 1 - k, k) == 0) {
                pi[i] = k;
                break;
            }
    return pi;
}

int main() {
    for (string s : {"aabaaab", "abcabcab", "aaaa", "abcd"}) {
        cout << s << ":";
        for (int x : prefixFunction(s)) cout << " " << x;
        cout << "\n";
    }
    // Check (not printed): equal to the definition on every string of length 1..9 over {a, b} and 1..6 over {a, b, c};
    // and the total number of fall-backs over a string never exceeds its length (the amortised bound of the proof).
    for (int sigma : {2, 3})
        for (int n = 1; n <= (sigma == 2 ? 9 : 6); n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= sigma;
            for (int code = 0; code < total; code++) {
                string s(n, 'a');
                for (int i = 0, c = code; i < n; i++, c /= sigma) s[i] = 'a' + c % sigma;
                if (prefixFunction(s) != slow(s)) return 1;
                vector<int> pi(n, 0);
                int fallbacks = 0;
                for (int i = 1; i < n; i++) {
                    int k = pi[i - 1];
                    while (k > 0 && s[i] != s[k]) k = pi[k - 1], fallbacks++;
                    if (s[i] == s[k]) k++;
                    pi[i] = k;
                }
                if (fallbacks > n) return 1;
            }
        }
}
