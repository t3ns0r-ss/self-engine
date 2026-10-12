#include <bits/stdc++.h>
using namespace std;

/*
Problem: a string s and q questions "a b len": compare the blocks of length len that start at a and b
(1-based) in dictionary order.
Input: s, q, then q lines a b len.
Output: <, = or > for each question (the first block against the second).
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
// Compare s[a..a+len) with s[b..b+len) in dictionary order: -1, 0 or 1. Uses the Hasher of the first template.
// Binary search the length k of the equal beginning (Theorem 6.1.4 applied to a prefix), then look at the next letters.
int compareBlocks(const string& s, const Hasher& hs, int a, int b, int len) {
    int lo = 0, hi = len;  // the longest k <= len with equal first k letters is in [lo, hi]
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (hs.hash(a, a + mid) == hs.hash(b, b + mid)) lo = mid;
        else hi = mid - 1;
    }
    if (lo == len) return 0;
    return s[a + lo] < s[b + lo] ? -1 : 1;
}
// snippet:end

int main() {
    string s;
    int q;
    cin >> s >> q;
    Hasher hs(s);
    while (q--) {
        int a, b, len;
        cin >> a >> b >> len;
        a--, b--;
        int c = compareBlocks(s, hs, a, b, len);
        cout << (c < 0 ? "<" : c == 0 ? "=" : ">") << "\n";
    }
}
