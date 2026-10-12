#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1110 Minimal Rotation. A rotation of a string moves characters one after another from the beginning
to the end. Print the lexicographically smallest rotation of the given string (length up to 10^6).
Input: the string. Output: its smallest rotation.
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

// Compare s[a..a+len) with s[b..b+len) in dictionary order: -1, 0 or 1 (template "Which block is smaller?").
int compareBlocks(const string& s, const Hasher& hs, int a, int b, int len) {
    int lo = 0, hi = len;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (hs.hash(a, a + mid) == hs.hash(b, b + mid)) lo = mid;
        else hi = mid - 1;
    }
    if (lo == len) return 0;
    return s[a + lo] < s[b + lo] ? -1 : 1;
}

// snippet:begin
// The smallest rotation of s: the rotations are the blocks of length n of s + s that start at 0, 1, ..., n - 1.
string minimalRotation(const string& s) {
    int n = s.size();
    string t = s + s;
    Hasher hs(t);
    int best = 0;  // the start of the smallest rotation found so far
    for (int i = 1; i < n; i++)
        if (compareBlocks(t, hs, i, best, n) < 0) best = i;
    return t.substr(best, n);
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << minimalRotation(s) << "\n";
}
