#include <bits/stdc++.h>
using namespace std;

/*
Problem: for every place i of the text s, the length of the longest common beginning of s[i..] and the pattern t.
Input: s, then t (lower-case letters, lengths up to 10^5).
Output: |s| numbers.
*/

vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// snippet:begin
// match[i] = the longest common beginning of s[i..] and t, for every i, from the Z-function of t + '#' + s
// (Theorem 6.2.5 (b)); the separator stops every value at |t|. Uses zFunction.
vector<int> prefixMatchLengths(const string& s, const string& t) {
    vector<int> z = zFunction(t + '#' + s), match(s.size());
    for (size_t i = 0; i < s.size(); i++) match[i] = z[t.size() + 1 + i];
    return match;
}
// snippet:end

int main() {
    string s, t;
    cin >> s >> t;
    vector<int> match = prefixMatchLengths(s, t);
    for (size_t i = 0; i < match.size(); i++) cout << match[i] << (i + 1 < match.size() ? ' ' : '\n');
}
