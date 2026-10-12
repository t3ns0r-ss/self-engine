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

int bruteDistinctBlocks(const string& s, int L) {
    set<string> seen;
    for (int i = 0; i + L <= (int)s.size(); i++) seen.insert(s.substr(i, L));
    return seen.size();
}
int hashDistinctBlocks(const string& s, int L) {
    PrefixHash ph(s, 911382323);
    vector<long long> hashes;
    for (int i = 0; i + L <= (int)s.size(); i++) hashes.push_back(ph.get(i, i + L));
    sort(hashes.begin(), hashes.end());
    return unique(hashes.begin(), hashes.end()) - hashes.begin();
}
// Distinct non-empty subsequences, by brute force over all 2^n choices of places.
int bruteDistinctSubsequences(const string& s) {
    int n = s.size();
    set<string> seen;
    for (int mask = 1; mask < (1 << n); mask++) {
        string t;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) t += s[i];
        seen.insert(t);
    }
    return seen.size();
}
// Distinct substrings of all lengths, by hash.
int hashDistinctSubstrings(const string& s) {
    int total = 0;
    for (int L = 1; L <= (int)s.size(); L++) total += hashDistinctBlocks(s, L);
    return total;
}

int main() {
    cout << "P1 brute=" << bruteDistinctBlocks("abababa", 2) << " method=" << hashDistinctBlocks("abababa", 2) << "\n";
    cout << "P2 brute=" << bruteDistinctBlocks("abcabcab", 3) << " method=" << hashDistinctBlocks("abcabcab", 3) << "\n";
    // N1: the question asks for distinct subsequences; counting distinct substrings answers a different question.
    cout << "N1 brute=" << bruteDistinctSubsequences("aba") << " method=" << hashDistinctSubstrings("aba") << "\n";
}
