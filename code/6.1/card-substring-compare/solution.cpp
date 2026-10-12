#include <bits/stdc++.h>
using namespace std;

const long long P = (1LL << 61) - 1;
long long mulmod(long long a, long long b) { return (__int128)a * b % P; }
// Letters a..z are 1..26 and '?' is 27 (so that a '?' is an ordinary letter for the hash).
int val(char c) { return c == '?' ? 27 : c - 'a' + 1; }
struct PrefixHash {
    vector<long long> h, pw;
    PrefixHash(const string& s, long long B) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = (mulmod(h[i], B) + val(s[i])) % P;
            pw[i + 1] = mulmod(pw[i], B);
        }
    }
    long long get(int l, int r) const { return (h[r] + P - mulmod(h[l], pw[r - l])) % P; }
};

// Number of lengths L (1 <= L <= n/2) with s[0..L) = s[L..2L), by comparing letters.
int bruteSquares(const string& s, bool wildcard) {
    int n = s.size(), count = 0;
    for (int L = 1; 2 * L <= n; L++) {
        bool same = true;
        for (int i = 0; i < L; i++) {
            char x = s[i], y = s[L + i];
            if (x != y && !(wildcard && (x == '?' || y == '?'))) same = false;
        }
        count += same;
    }
    return count;
}
int hashSquares(const string& s) {
    PrefixHash ph(s, 911382323);
    int n = s.size(), count = 0;
    for (int L = 1; 2 * L <= n; L++) count += ph.get(0, L) == ph.get(L, 2 * L);
    return count;
}

int main() {
    // P1, P2: the question is plain equality of two blocks.
    cout << "P1 brute=" << bruteSquares("abababab", false) << " method=" << hashSquares("abababab") << "\n";
    cout << "P2 brute=" << bruteSquares("aaaaaa", false) << " method=" << hashSquares("aaaaaa") << "\n";
    // N1: '?' matches any letter, so equality is not the question; the hash treats '?' as a letter.
    cout << "N1 brute=" << bruteSquares("ab?b", true) << " method=" << hashSquares("ab?b") << "\n";
}
