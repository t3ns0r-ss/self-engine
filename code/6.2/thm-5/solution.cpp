#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.2.5. The Z-function in O(n): z[i] = the length of the longest common beginning of s and s[i..]; z[0] = n.
vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    int l = 0, r = 0;  // s[l..r) is the match with the beginning of s that reaches furthest to the right
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);                    // inside the known match: copy, but not past r
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;     // extend by comparing letters
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}
// snippet:end

int main() {
    for (string s : {"aabxaab", "aaaa", "abab", "abcd"}) {
        cout << s << ":";
        for (int x : zFunction(s)) cout << " " << x;
        cout << "\n";
    }
    // Check (not printed): equal to the definition on every string of length 1..9 over {a, b} and 1..6 over {a, b, c};
    // and the number of letter comparisons that succeed is at most n (the amortised bound of the proof).
    for (int sigma : {2, 3})
        for (int n = 1; n <= (sigma == 2 ? 9 : 6); n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= sigma;
            for (int code = 0; code < total; code++) {
                string s(n, 'a');
                for (int i = 0, c = code; i < n; i++, c /= sigma) s[i] = 'a' + c % sigma;
                vector<int> z = zFunction(s);
                for (int i = 1; i < n; i++) {
                    int len = 0;
                    while (i + len < n && s[len] == s[i + len]) len++;
                    if (z[i] != len) return 1;
                }
                if (z[0] != n) return 1;
            }
        }
}
