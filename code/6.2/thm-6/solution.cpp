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
// Theorem 6.2.6. occ[k] = the number of places where the prefix of length k occurs in s (k = 1..n). Uses prefixFunction.
vector<int> prefixOccurrences(const string& s) {
    int n = s.size();
    vector<int> pi = prefixFunction(s), occ(n + 1, 0);
    for (int i = 0; i < n; i++) occ[pi[i]]++;           // the longest border of s[0..i] has length pi[i]
    for (int k = n; k >= 1; k--) occ[pi[k - 1]] += occ[k];  // an end of the prefix k is also an end of its longest border
    for (int k = 1; k <= n; k++) occ[k]++;              // the prefix k itself, at the place 0
    return occ;
}
// snippet:end

int main() {
    for (string s : {"aaa", "abab", "abcabcab"}) {
        vector<int> occ = prefixOccurrences(s);
        cout << s << ":";
        for (size_t k = 1; k < occ.size(); k++) cout << " " << occ[k];
        cout << "\n";
    }
    // Check (not printed): equal to counting the starts directly, on every string of length 1..10 over {a, b}
    // and 1..6 over {a, b, c}.
    for (int sigma : {2, 3})
        for (int n = 1; n <= (sigma == 2 ? 10 : 6); n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= sigma;
            for (int code = 0; code < total; code++) {
                string s(n, 'a');
                for (int i = 0, c = code; i < n; i++, c /= sigma) s[i] = 'a' + c % sigma;
                vector<int> occ = prefixOccurrences(s);
                for (int k = 1; k <= n; k++) {
                    int count = 0;
                    for (int i = 0; i + k <= n; i++) count += s.compare(i, k, s, 0, k) == 0;
                    if (occ[k] != count) return 1;
                }
            }
        }
}
