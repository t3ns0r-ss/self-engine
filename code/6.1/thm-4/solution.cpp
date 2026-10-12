#include <bits/stdc++.h>
using namespace std;

const long long P = (1LL << 61) - 1;
long long mulmod(long long a, long long b) { return (__int128)a * b % P; }
struct PrefixHash {
    vector<long long> h, pw;
    PrefixHash(const string& s, long long B) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = (mulmod(h[i], B) + (s[i] - 'a' + 1)) % P;
            pw[i + 1] = mulmod(pw[i], B);
        }
    }
    long long get(int l, int r) const { return (h[r] + P - mulmod(h[l], pw[r - l])) % P; }
};

// snippet:begin
// Theorem 6.1.4. Does some block of length L occur at two different places of s? Sort the hashes of all windows.
bool hasRepeat(const PrefixHash& ph, int n, int L) {
    vector<long long> hashes;
    for (int i = 0; i + L <= n; i++) hashes.push_back(ph.get(i, i + L));
    sort(hashes.begin(), hashes.end());
    return adjacent_find(hashes.begin(), hashes.end()) != hashes.end();
}
// The longest block that occurs twice (the two places may overlap); 0 if there is none. Binary search on L.
int longestRepeat(const string& s, long long B) {
    PrefixHash ph(s, B);
    int n = s.size(), lo = 0, hi = n - 1;  // a repeat exists for L = lo; the answer is in [lo, hi]
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (hasRepeat(ph, n, mid)) lo = mid;  // true at mid: the answer is mid or more
        else hi = mid - 1;                     // false at mid: the answer is smaller
    }
    return lo;
}
// snippet:end

int bruteRepeat(const string& s) {
    int n = s.size(), best = 0;
    for (int L = 1; L < n; L++)
        for (int i = 0; i + L <= n; i++)
            for (int j = i + 1; j + L <= n; j++)
                if (s.compare(i, L, s, j, L) == 0) best = L;
    return best;
}

int main() {
    for (string s : {"banana", "abcd", "aaaa", "abab"}) cout << s << ": " << longestRepeat(s, 911382323) << "\n";
    // Check (not printed): same as the brute force on every string of length 1..9 over {a, b}
    // and every string of length 1..6 over {a, b, c}.
    for (int sigma : {2, 3})
        for (int n = 1; n <= (sigma == 2 ? 9 : 6); n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= sigma;
            for (int code = 0; code < total; code++) {
                string s(n, 'a');
                for (int i = 0, c = code; i < n; i++, c /= sigma) s[i] = 'a' + c % sigma;
                if (longestRepeat(s, 911382323) != bruteRepeat(s)) return 1;
            }
        }
}
