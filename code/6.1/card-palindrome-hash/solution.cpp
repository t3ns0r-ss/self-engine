#include <bits/stdc++.h>
using namespace std;

const long long P = (1LL << 61) - 1;
long long mulmod(long long a, long long b) { return (__int128)a * b % P; }
struct PrefixHash {
    vector<long long> h, pw;
    PrefixHash(const string& s, long long B) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = (mulmod(h[i], B) + (s[i] - 'a' + 1)) % P;
            pw[i + 1] = mulmod(pw[i], B);
        }
    }
    long long get(int l, int r) const { return (h[r] + P - mulmod(h[l], pw[r - l])) % P; }
};

// Longest palindromic substring by hash: for every centre binary search the radius (odd and even lengths).
int hashLongestPalindrome(const string& s) {
    string t(s.rbegin(), s.rend());
    PrefixHash fwd(s, 911382323), rev(t, 911382323);
    int n = s.size(), best = 1;
    auto isPal = [&](int l, int r) { return fwd.get(l, r) == rev.get(n - r, n - l); };
    for (int c = 0; c < n; c++) {
        int lo = 0, hi = min(c, n - 1 - c);  // odd: s[c-k..c+k]
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (isPal(c - mid, c + mid + 1)) lo = mid;
            else hi = mid - 1;
        }
        best = max(best, 2 * lo + 1);
        lo = 0, hi = min(c + 1, n - c - 1);  // even: s[c-k+1..c+k]
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (isPal(c - mid + 1, c + mid + 1)) lo = mid;
            else hi = mid - 1;
        }
        best = max(best, 2 * lo);
    }
    return best;
}
int bruteLongestPalindrome(const string& s) {
    int n = s.size(), best = 0;
    for (int l = 0; l < n; l++)
        for (int r = l + 1; r <= n; r++) {
            string u = s.substr(l, r - l), v(u.rbegin(), u.rend());
            if (u == v) best = max(best, r - l);
        }
    return best;
}
// Longest palindromic subsequence by the table over ends.
int bruteLongestPalindromicSubsequence(const string& s) {
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int l = n - 1; l >= 0; l--) {
        dp[l][l + 1] = 1;
        for (int r = l + 2; r <= n; r++)
            dp[l][r] = s[l] == s[r - 1] ? dp[l + 1][r - 1] + 2 : max(dp[l + 1][r], dp[l][r - 1]);
    }
    return dp[0][n];
}

int main() {
    for (auto [name, s] : {make_pair("P1", string("forgeeksskeegfor")), make_pair("P2", string("abacdfgdcaba"))})
        cout << name << " brute=" << bruteLongestPalindrome(s) << " method=" << hashLongestPalindrome(s) << "\n";
    // N1: the question asks for a subsequence; the hash method finds substrings only.
    cout << "N1 brute=" << bruteLongestPalindromicSubsequence("agbcba") << " method=" << hashLongestPalindrome("agbcba") << "\n";
}
