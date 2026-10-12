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
// Theorem 6.1.5. fwd = prefix hashes of s, rev = prefix hashes of the reversed s, n = |s|.
// Is s[l..r) a palindrome? The reversed block is the block [n-r, n-l) of the reversed string.
bool isPalindrome(const PrefixHash& fwd, const PrefixHash& rev, int n, int l, int r) {
    return fwd.get(l, r) == rev.get(n - r, n - l);
}
// Largest k such that s[c-k..c+k] is a palindrome (odd length, centre c). Binary search, valid because
// if the block of radius k is a palindrome, so is the block of radius k - 1.
int oddRadius(const PrefixHash& fwd, const PrefixHash& rev, int n, int c) {
    int lo = 0, hi = min(c, n - 1 - c);
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (isPalindrome(fwd, rev, n, c - mid, c + mid + 1)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
// snippet:end

bool bruteIsPal(const string& s, int l, int r) {
    for (int i = l, j = r - 1; i < j; i++, j--)
        if (s[i] != s[j]) return false;
    return true;
}

int main() {
    auto show = [&](const string& s, int l, int r) {
        string t(s.rbegin(), s.rend());
        PrefixHash fwd(s, 911382323), rev(t, 911382323);
        cout << s << " [" << l << "," << r << ") palindrome: " << isPalindrome(fwd, rev, s.size(), l, r) << "\n";
    };
    show("abacaba", 0, 7);
    show("abacaba", 1, 4);
    show("abba", 0, 4);
    show("abca", 0, 4);
    {
        string s = "xabax", t(s.rbegin(), s.rend());
        PrefixHash fwd(s, 911382323), rev(t, 911382323);
        cout << s << " radius at 2: " << oddRadius(fwd, rev, s.size(), 2) << "\n";
        string u = "abacaba", w(u.rbegin(), u.rend());
        PrefixHash f2(u, 911382323), r2(w, 911382323);
        cout << u << " radius at 3: " << oddRadius(f2, r2, u.size(), 3) << "\n";
    }
    // Check (not printed): both functions agree with direct comparison on every string of length 1..10
    // over {a, b} and every string of length 1..6 over {a, b, c}, for every block and every centre.
    for (int sigma : {2, 3})
        for (int n = 1; n <= (sigma == 2 ? 10 : 6); n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= sigma;
            for (int code = 0; code < total; code++) {
                string s(n, 'a');
                for (int i = 0, c = code; i < n; i++, c /= sigma) s[i] = 'a' + c % sigma;
                string t(s.rbegin(), s.rend());
                PrefixHash fwd(s, 911382323), rev(t, 911382323);
                for (int l = 0; l <= n; l++)
                    for (int r = l; r <= n; r++)
                        if (isPalindrome(fwd, rev, n, l, r) != bruteIsPal(s, l, r)) return 1;
                for (int c = 0; c < n; c++) {
                    int k = 0;
                    while (c - k - 1 >= 0 && c + k + 1 < n && s[c - k - 1] == s[c + k + 1]) k++;
                    if (oddRadius(fwd, rev, n, c) != k) return 1;
                }
            }
        }
}
