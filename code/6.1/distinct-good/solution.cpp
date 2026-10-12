#include <bits/stdc++.h>
using namespace std;

/*
Problem: count the different substrings of a string s that contain at most k bad letters.
Input: s (lower-case letters, length up to 1500); a line of 26 characters 0/1 (the i-th is 1 if the letter
number i is bad); then k.
Output: the number of different substrings with at most k bad letters.
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
// Number of different substrings of s with at most k bad letters (bad[c] is 1 for a bad letter c, 0..25).
// Uses the Hasher of the first template. Different lengths are mixed in one list: every letter value is at
// least 1, so a longer string never has the hash of a shorter one except by a collision.
int countGood(const string& s, const vector<int>& bad, int k) {
    Hasher hs(s);
    int n = s.size();
    vector<long long> hashes;
    for (int l = 0; l < n; l++) {
        int badCount = 0;
        for (int r = l; r < n; r++) {  // the substring s[l..r]
            badCount += bad[s[r] - 'a'];
            if (badCount > k) break;   // longer substrings from l only get more bad letters
            hashes.push_back(hs.hash(l, r + 1));
        }
    }
    sort(hashes.begin(), hashes.end());
    return unique(hashes.begin(), hashes.end()) - hashes.begin();
}
// snippet:end

int main() {
    string s, flags;
    int k;
    cin >> s >> flags >> k;
    vector<int> bad(26);
    for (int i = 0; i < 26; i++) bad[i] = flags[i] - '0';
    cout << countGood(s, bad, k) << "\n";
}
