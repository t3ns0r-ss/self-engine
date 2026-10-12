#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.1.1. Prefix hashes of a string over the letters a..z (a = 1, ..., z = 26); get(l, r) is the hash of s[l..r) in O(1).
const long long P = (1LL << 61) - 1;  // a prime, about 2.3 * 10^18
long long mulmod(long long a, long long b) { return (__int128)a * b % P; }  // the product needs up to 122 bits
struct PrefixHash {
    vector<long long> h, pw;  // h[i] = hash of s[0..i), pw[i] = B^i mod P
    PrefixHash(const string& s, long long B) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = (mulmod(h[i], B) + (s[i] - 'a' + 1)) % P;
            pw[i + 1] = mulmod(pw[i], B);
        }
    }
    long long get(int l, int r) const { return (h[r] + P - mulmod(h[l], pw[r - l])) % P; }
};
// snippet:end

// The value of the string by its definition: s[0] * B^(m-1) + ... + s[m-1], modulo P.
long long direct(const string& t, long long B) {
    long long v = 0;
    for (char c : t) v = (mulmod(v, B) + (c - 'a' + 1)) % P;
    return v;
}

bool millerRabin(unsigned long long n) {
    unsigned long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) d /= 2, r++;
    auto power = [&](unsigned long long b, unsigned long long e) {
        unsigned long long res = 1;
        for (b %= n; e; e >>= 1, b = (unsigned __int128)b * b % n)
            if (e & 1) res = (unsigned __int128)res * b % n;
        return res;
    };
    for (unsigned long long a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        unsigned long long x = power(a, d);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 1; i < r && composite; i++) {
            x = (unsigned __int128)x * x % n;
            if (x == n - 1) composite = false;
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    {
        string s = "abcde";
        PrefixHash ph(s, 10);
        cout << s << " h =";
        for (long long v : ph.h) cout << " " << v;
        cout << "\n";
        cout << s << " [1,4) = " << ph.get(1, 4) << "\n";
        cout << s << " [2,5) = " << ph.get(2, 5) << "\n";
    }
    {
        string s = "abab";
        PrefixHash ph(s, 10);
        cout << s << " [0,2) = " << ph.get(0, 2) << ", [2,4) = " << ph.get(2, 4) << "\n";
    }
    {
        string s = "aa";
        PrefixHash ph(s, 10);
        cout << s << " [0,1) = " << ph.get(0, 1) << ", [1,2) = " << ph.get(1, 2) << "\n";
    }
    // Checks (not printed): the modulus is prime, and get() equals the definition for every substring of
    // every string of length 1..7 over {a, b, c}, for three different bases.
    if (!millerRabin(P)) return 1;
    mt19937_64 rng(12345);
    for (long long B : {10LL, 911382323LL, (long long)(rng() % (P - 1000) + 500)})
        for (int n = 1; n <= 7; n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= 3;
            for (int code = 0; code < total; code++) {
                string s(n, 'a');
                for (int i = 0, c = code; i < n; i++, c /= 3) s[i] = 'a' + c % 3;
                PrefixHash ph(s, B);
                for (int l = 0; l <= n; l++)
                    for (int r = l; r <= n; r++)
                        if (ph.get(l, r) != direct(s.substr(l, r - l), B)) return 1;
            }
        }
}
