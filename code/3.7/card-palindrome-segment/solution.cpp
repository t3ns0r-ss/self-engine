#include <bits/stdc++.h>
using namespace std;

int lps(const string& s) {
    int n = s.size();
    vector<vector<int>> P(n + 2, vector<int>(n + 2, 0));
    for (int l = 1; l <= n; l++) P[l][l] = 1;
    for (int len = 2; len <= n; len++) for (int l = 1; l + len - 1 <= n; l++) {
        int r = l + len - 1;
        P[l][r] = s[l - 1] == s[r - 1] ? P[l + 1][r - 1] + 2 : max(P[l + 1][r], P[l][r - 1]);
    }
    return P[1][n];
}
int bruteSubsequence(const string& t) {
    int best = 0;
    for (int mask = 1; mask < (1 << t.size()); mask++) {
        string u;
        for (size_t i = 0; i < t.size(); i++) if (mask >> i & 1) u += t[i];
        string v(u.rbegin(), u.rend());
        if (u == v) best = max(best, (int)u.size());
    }
    return best;
}
int main() {
    // P1: the longest palindromic subsequence of abcab. P2: the fewest insertions to make abcab a palindrome (n minus that length).
    cout << "P1 brute=" << bruteSubsequence("abcab") << " method=" << lps("abcab") << '\n';
    cout << "P2 brute=" << 5 - bruteSubsequence("abcab") << " method=" << 5 - lps("abcab") << '\n';
    // N1: the longest contiguous palindrome of abcab, computed as the longest palindromic subsequence.
    string s = "abcab";
    int best = 0;
    for (size_t l = 0; l < s.size(); l++) for (size_t r = l; r < s.size(); r++) {
        string u = s.substr(l, r - l + 1), v(u.rbegin(), u.rend());
        if (u == v) best = max(best, (int)u.size());
    }
    cout << "N1 brute=" << best << " method=" << lps(s) << '\n';
    // N2: the longest palindrome that can be built by rearranging the letters of abcab: pairs of equal letters plus one in the middle.
    map<char, int> cnt;
    for (char c : s) cnt[c]++;
    int length = 0;
    bool odd = false;
    for (auto [c, k] : cnt) length += k / 2 * 2, odd |= k % 2;
    cout << "N2 brute=" << length + odd << " method=" << lps(s) << '\n';
}
