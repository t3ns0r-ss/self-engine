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
// Theorem 6.2.4 (a). The start places of the occurrences of the pattern t in the text s. Uses prefixFunction
// (Theorem 6.2.3); the separator '#' must not occur in t or s.
vector<int> occurrences(const string& t, const string& s) {
    string w = t + '#' + s;
    vector<int> pi = prefixFunction(w), starts;
    int m = t.size();
    for (size_t j = 0; j < s.size(); j++)
        if (pi[m + 1 + j] == m) starts.push_back(j + 1 - m);  // a border of length m ends at the place j of the text
    return starts;
}
// Theorem 6.2.4 (b). The matching automaton of t over the letters 'a'..'z':
// next[k][c] = the length of the longest prefix of t that is a suffix of (the k letters of t read so far) + c.
vector<array<int, 26>> automaton(const string& t) {
    int m = t.size();
    vector<int> pi = prefixFunction(t);
    vector<array<int, 26>> next(m + 1);
    for (int k = 0; k <= m; k++)
        for (int c = 0; c < 26; c++) {
            if (k < m && t[k] - 'a' == c) next[k][c] = k + 1;  // the next letter of the pattern: one more matched
            else next[k][c] = k == 0 ? 0 : next[pi[k - 1]][c];  // fall back to the longest border and try again
        }
    return next;
}
// snippet:end

int main() {
    auto show = [&](const string& t, const string& s) {
        cout << "t=" << t << " s=" << s << ":";
        vector<int> r = occurrences(t, s);
        if (r.empty()) cout << " none";
        for (int x : r) cout << " " << x;
        cout << "\n";
    };
    show("aba", "ababa");
    show("aa", "aaaa");
    show("abc", "abab");
    {
        string t = "aba";
        auto next = automaton(t);
        cout << "automaton of aba, from state 0 reading ababa:";
        int k = 0;
        for (char c : string("ababa")) {
            k = next[k][c - 'a'];
            cout << " " << k;
        }
        cout << "\n";
    }
    // Check (not printed): the occurrences equal those found by comparing at every start, and the automaton state after each
    // letter equals the longest prefix of t that is a suffix of the text read so far, on all pairs of strings with
    // |t| in 1..4 and |s| in 1..8 over {a, b}.
    for (int m = 1; m <= 4; m++)
        for (int n = 1; n <= 8; n++) {
            int tt = 1 << m, ts = 1 << n;
            for (int a = 0; a < tt; a++)
                for (int b = 0; b < ts; b++) {
                    string t(m, 'a'), s(n, 'a');
                    for (int i = 0; i < m; i++) t[i] = 'a' + (a >> i & 1);
                    for (int i = 0; i < n; i++) s[i] = 'a' + (b >> i & 1);
                    vector<int> want;
                    for (int i = 0; i + m <= n; i++)
                        if (s.compare(i, m, t) == 0) want.push_back(i);
                    if (occurrences(t, s) != want) return 1;
                    auto next = automaton(t);
                    int k = 0;
                    for (int j = 0; j < n; j++) {
                        k = next[k][s[j] - 'a'];
                        int best = 0;
                        for (int len = 1; len <= min(m, j + 1); len++)
                            if (s.compare(j + 1 - len, len, t, 0, len) == 0) best = len;
                        if (k != best) return 1;
                    }
                }
        }
}
