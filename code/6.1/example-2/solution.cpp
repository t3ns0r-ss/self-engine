#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 2106 Repeating Substring. Print the longest substring that occurs in two (or more) places of the
given string (length up to 10^5), or -1 if there is none. This unit prints the one that starts first, as the
judge accepts any.
Input: the string. Output: that substring or -1.
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
// The longest block that occurs at two different places of s (the copies may overlap), or "-1".
// Binary search on the length L (Theorem 6.1.4); a test for L sorts the hashes of all windows.
string longestRepeating(const string& s) {
    int n = s.size();
    Hasher hs(s);
    auto repeated = [&](int L) {  // does some block of length L occur twice?
        vector<long long> hashes;
        for (int i = 0; i + L <= n; i++) hashes.push_back(hs.hash(i, i + L));
        sort(hashes.begin(), hashes.end());
        return adjacent_find(hashes.begin(), hashes.end()) != hashes.end();
    };
    int lo = 0, hi = n - 1;  // the longest repeated length is in [lo, hi]; L = 0 counts as repeated
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (repeated(mid)) lo = mid;
        else hi = mid - 1;
    }
    if (lo == 0) return "-1";
    map<long long, int> count;  // the first block of length lo whose hash occurs twice
    for (int i = 0; i + lo <= n; i++) count[hs.hash(i, i + lo)]++;
    for (int i = 0; i + lo <= n; i++)
        if (count[hs.hash(i, i + lo)] >= 2) return s.substr(i, lo);
    return "-1";
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << longestRepeating(s) << "\n";
}
