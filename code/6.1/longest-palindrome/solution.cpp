#include <bits/stdc++.h>
using namespace std;

/*
Problem: the length of the longest palindromic substring of s (lower-case letters).
Input: s (length up to 10^6).
Output: the length.
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
// The longest palindromic substring, by a binary search on the radius around every centre (Theorem 6.1.5).
// Uses the Hasher of the first template, built for s and for the reversed s with the same base.
int longestPalindrome(const string& s) {
    int n = s.size();
    string t(s.rbegin(), s.rend());
    Hasher fwd(s), rev(t);
    auto isPal = [&](int l, int r) { return fwd.hash(l, r) == rev.hash(n - r, n - l); };  // is s[l..r) a palindrome?
    int best = 1;
    for (int c = 0; c < n; c++) {
        int lo = 0, hi = min(c, n - 1 - c);  // odd length: s[c-k..c+k]
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (isPal(c - mid, c + mid + 1)) lo = mid;
            else hi = mid - 1;
        }
        best = max(best, 2 * lo + 1);
        lo = 0, hi = min(c + 1, n - c - 1);  // even length: s[c-k+1..c+k]
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (isPal(c - mid + 1, c + mid + 1)) lo = mid;
            else hi = mid - 1;
        }
        best = max(best, 2 * lo);
    }
    return best;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << longestPalindrome(s) << "\n";
}
