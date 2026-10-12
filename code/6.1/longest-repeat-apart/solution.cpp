#include <bits/stdc++.h>
using namespace std;

/*
Problem: the longest block of a string s that appears twice without the two copies sharing a place.
Input: n, then s (lower-case letters).
Output: the length of the longest such block (0 if there is none).
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
// Is there a block of length L that starts at two places i < j with j - i >= L (the copies do not overlap)?
// Uses the Hasher of the first template. Sorting (hash, start) pairs puts equal hashes together, earliest start first.
bool hasApartRepeat(const Hasher& hs, int n, int L) {
    vector<pair<long long, int>> windows;
    for (int i = 0; i + L <= n; i++) windows.push_back({hs.hash(i, i + L), i});
    sort(windows.begin(), windows.end());
    for (size_t a = 0, b; a < windows.size(); a = b) {
        for (b = a; b < windows.size() && windows[b].first == windows[a].first; b++) {}
        if (windows[b - 1].second - windows[a].second >= L) return true;  // earliest and latest start of this block
    }
    return false;
}
// The longest block with two non-overlapping copies: binary search on L (Theorem 6.1.4; shortening both copies keeps them apart).
int longestApartRepeat(const string& s) {
    Hasher hs(s);
    int n = s.size(), lo = 0, hi = n / 2;  // a copy pair needs 2L <= n
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (hasApartRepeat(hs, n, mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
// snippet:end

int main() {
    int n;
    string s;
    cin >> n >> s;
    cout << longestApartRepeat(s) << "\n";
}
