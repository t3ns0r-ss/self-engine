#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.2.1. pi[i] = the length of the longest border of s[0..i] (a proper prefix that is also a suffix), 0 if none.
// This is the definition itself, tried from the longest candidate down; it is slow and is here only to read.
vector<int> prefixFunctionSlow(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 0; i < n; i++)
        for (int k = i; k >= 1; k--)  // k = the length of the candidate border of s[0..i]
            if (s.compare(0, k, s, i + 1 - k, k) == 0) {
                pi[i] = k;
                break;
            }
    return pi;
}
// All border lengths of s[0..m), longest first: pi[m-1], then pi[pi[m-1]-1], and so on down to 0.
vector<int> borderLengths(const vector<int>& pi, int m) {
    vector<int> result;
    for (int k = pi[m - 1]; k > 0; k = pi[k - 1]) result.push_back(k);
    return result;
}
// The smallest period of s[0..m) is m - pi[m-1]; if it divides m, the string is that block repeated m / period times.
int smallestPeriod(const vector<int>& pi, int m) { return m - pi[m - 1]; }
// snippet:end

string show(const vector<int>& v) {
    string r;
    for (int x : v) r += (r.empty() ? "" : " ") + to_string(x);
    return r.empty() ? "-" : r;
}

int main() {
    for (string s : {"abcabcab", "abababab", "aaaa", "abcd"}) {
        vector<int> pi = prefixFunctionSlow(s);
        int m = s.size(), p = smallestPeriod(pi, m);
        cout << s << ": pi = " << show(pi) << "; borders = " << show(borderLengths(pi, m)) << "; period = " << p
             << (m % p == 0 && p < m ? ", repeated " + to_string(m / p) + " times" : "") << "\n";
    }
    // Check (not printed): on every string of length 1..8 over {a, b} and 1..6 over {a, b, c}, the chain gives exactly
    // the border lengths found by trying all lengths, and m - pi[m-1] is the smallest period found by trying all periods.
    for (int sigma : {2, 3})
        for (int n = 1; n <= (sigma == 2 ? 8 : 6); n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= sigma;
            for (int code = 0; code < total; code++) {
                string s(n, 'a');
                for (int i = 0, c = code; i < n; i++, c /= sigma) s[i] = 'a' + c % sigma;
                vector<int> pi = prefixFunctionSlow(s);
                vector<int> want;
                for (int k = n - 1; k >= 1; k--)
                    if (s.compare(0, k, s, n - k, k) == 0) want.push_back(k);
                if (borderLengths(pi, n) != want) return 1;
                int period = n;
                for (int p = n - 1; p >= 1; p--) {
                    bool ok = true;
                    for (int i = 0; i + p < n; i++) ok = ok && s[i] == s[i + p];
                    if (ok) period = p;
                }
                if (smallestPeriod(pi, n) != period) return 1;
            }
        }
}
