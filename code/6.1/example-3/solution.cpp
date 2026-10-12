#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1111 Longest Palindrome. Print the longest palindromic substring of the given string (length up
to 10^6). This unit prints the one that starts first, as the judge accepts any.
Input: the string. Output: that substring.
*/

const long long P = (1LL << 61) - 1;
long long mulmod(long long a, long long b) { return (__int128)a * b % P; }
struct Hasher {
    vector<long long> h, pw;
    Hasher(const string& s) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        static const long long B = rng() % (P - 1000) + 500;
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = (mulmod(h[i], B) + (s[i] - 'a' + 1)) % P;
            pw[i + 1] = mulmod(pw[i], B);
        }
    }
    long long hash(int l, int r) const { return (h[r] + P - mulmod(h[l], pw[r - l])) % P; }
};

// snippet:begin
// The longest palindromic substring (the leftmost one on ties): binary search on the radius around every centre.
// Uses the Hasher of the first template, for s and for the reversed s with the same base.
string longestPalindromeBlock(const string& s) {
    int n = s.size();
    string t(s.rbegin(), s.rend());
    Hasher fwd(s), rev(t);
    auto isPal = [&](int l, int r) { return fwd.hash(l, r) == rev.hash(n - r, n - l); };  // is s[l..r) a palindrome?
    int bestStart = 0, bestLen = 1;
    auto offer = [&](int start, int len) {  // keep the longer block, and the earlier one on equal lengths
        if (len > bestLen || (len == bestLen && start < bestStart)) bestStart = start, bestLen = len;
    };
    for (int c = 0; c < n; c++) {
        int lo = 0, hi = min(c, n - 1 - c);  // odd length: s[c-k..c+k]
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (isPal(c - mid, c + mid + 1)) lo = mid;
            else hi = mid - 1;
        }
        offer(c - lo, 2 * lo + 1);
        lo = 0, hi = min(c + 1, n - c - 1);  // even length: s[c-k+1..c+k]
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (isPal(c - mid + 1, c + mid + 1)) lo = mid;
            else hi = mid - 1;
        }
        if (lo > 0) offer(c - lo + 1, 2 * lo);
    }
    return s.substr(bestStart, bestLen);
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << longestPalindromeBlock(s) << "\n";
}
