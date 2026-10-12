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

int bruteSmallestPeriod(const string& s) {
    int n = s.size();
    for (int p = 1; p < n; p++) {
        bool ok = true;
        for (int i = 0; i + p < n; i++) ok = ok && s[i] == s[i + p];
        if (ok) return p;
    }
    return n;
}
// How many times is a block repeated (0 if the string is not a repetition of a shorter block)?
int bruteRepeats(const string& s) {
    int n = s.size();
    for (int len = 1; len < n; len++) {
        if (n % len) continue;
        bool ok = true;
        for (int i = len; i < n; i++) ok = ok && s[i] == s[i - len];
        if (ok) return n / len;
    }
    return 0;
}
int methodRepeats(const string& s) {
    int n = s.size(), q = n - prefixFunction(s)[n - 1];
    return (q < n && n % q == 0) ? n / q : 0;
}
// The longest prefix equal to the reverse of the suffix of the same length (the whole string allowed).
int bruteMirror(const string& s) {
    int n = s.size(), best = 0;
    for (int k = 1; k <= n; k++) {
        string suffix = s.substr(n - k), reversed(suffix.rbegin(), suffix.rend());
        if (s.compare(0, k, reversed) == 0) best = k;
    }
    return best;
}

int main() {
    string a = "abcabcab", b = "abababab", c = "abcba";
    cout << "P1 brute=" << bruteSmallestPeriod(a) << " method=" << a.size() - prefixFunction(a).back() << "\n";
    cout << "P2 brute=" << bruteRepeats(b) << " method=" << methodRepeats(b) << "\n";
    // N1: a prefix equal to the REVERSE of a suffix is not a border; the longest border is only the last prefix-function value.
    cout << "N1 brute=" << bruteMirror(c) << " method=" << prefixFunction(c).back() << "\n";
}
