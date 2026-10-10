#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.6.1. Filling by length: a segment's value uses only shorter segments inside it, so the lengths are the outer loop.
// Here, which segments of s are palindromes: pal[l][r] needs pal[l + 1][r - 1].
vector<vector<char>> palindromeTable(const string& s) {
    int n = s.size();
    vector<vector<char>> pal(n, vector<char>(n, 0));
    for (int len = 1; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            pal[l][r] = s[l] == s[r] && (len <= 2 || pal[l + 1][r - 1]);
        }
    return pal;
}
// snippet:end

int main() {
    string s = "abaca";
    auto pal = palindromeTable(s);
    int count = 0;
    cout << "palindromic segments of abaca:";
    for (int l = 0; l < 5; l++) for (int r = l; r < 5; r++) if (pal[l][r]) count++, cout << ' ' << s.substr(l, r - l + 1);
    cout << " (" << count << ")\n";
    mt19937 rng(51);
    for (int round = 0; round < 300; round++) {
        string t;
        for (int i = 1 + rng() % 9; i > 0; i--) t += 'a' + rng() % 3;
        auto p = palindromeTable(t);
        for (size_t l = 0; l < t.size(); l++) for (size_t r = l; r < t.size(); r++) {
            string u = t.substr(l, r - l + 1), v(u.rbegin(), u.rend());
            if ((u == v) != (bool)p[l][r]) return 1;
        }
    }
}
