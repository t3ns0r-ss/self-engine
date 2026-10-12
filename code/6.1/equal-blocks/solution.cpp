#include <bits/stdc++.h>
using namespace std;

/*
Problem: a string s of lower-case letters and q questions "a b len": are the blocks of length len that start at
the places a and b (1-based) equal?
Input: s, then q, then q lines a b len (the blocks lie inside s).
Output: YES or NO for each question.
*/

// snippet:begin
// Prefix hashes of a lower-case string with a random base: hash(l, r) is the hash of s[l..r) in O(1).
const long long P = (1LL << 61) - 1;  // a prime
long long mulmod(long long a, long long b) { return (__int128)a * b % P; }
struct Hasher {
    vector<long long> h, pw;  // h[i] = hash of s[0..i), pw[i] = B^i
    Hasher(const string& s) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        static const long long B = rng() % (P - 1000) + 500;  // random base, chosen once per run
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = (mulmod(h[i], B) + (s[i] - 'a' + 1)) % P;
            pw[i + 1] = mulmod(pw[i], B);
        }
    }
    long long hash(int l, int r) const { return (h[r] + P - mulmod(h[l], pw[r - l])) % P; }
};
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
        cout << (hs.hash(a, a + len) == hs.hash(b, b + len) ? "YES" : "NO") << "\n";
    }
}
