#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.6.4. P[l][r] = the longest palindromic subsequence of s[l..r]: both ends if they match, otherwise drop one end.
int palindromicSubsequence(const string& s) {
    int n = s.size();
    vector<vector<int>> P(n + 2, vector<int>(n + 2, 0));
    for (int l = 0; l < n; l++) P[l + 1][l + 1] = 1;
    for (int len = 2; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            P[l][r] = s[l - 1] == s[r - 1] ? P[l + 1][r - 1] + 2 : max(P[l + 1][r], P[l][r - 1]);
        }
    return n ? P[1][n] : 0;
}
// snippet:end

int main() {
    cout << "longest palindromic subsequence of abcab: " << palindromicSubsequence("abcab") << '\n';
    mt19937 rng(54);
    for (int round = 0; round < 300; round++) {
        string t;
        for (int i = 1 + rng() % 10; i > 0; i--) t += 'a' + rng() % 3;
        int best = 0;
        for (int mask = 1; mask < (1 << t.size()); mask++) {
            string u;
            for (size_t i = 0; i < t.size(); i++) if (mask >> i & 1) u += t[i];
            string v(u.rbegin(), u.rend());
            if (u == v) best = max(best, (int)u.size());
        }
        if (best != palindromicSubsequence(t)) return 1;
    }
}
