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

// How many times does the most frequent block of length L occur? (by hash)
int maxFrequency(const PrefixHash& ph, int n, int L) {
    vector<long long> hashes;
    for (int i = 0; i + L <= n; i++) hashes.push_back(ph.get(i, i + L));
    sort(hashes.begin(), hashes.end());
    int best = 0;
    for (size_t i = 0, j; i < hashes.size(); i = j) {
        for (j = i; j < hashes.size() && hashes[j] == hashes[i]; j++) {}
        best = max(best, (int)(j - i));
    }
    return best;
}
// How many times does the block s[i..i+L) occur? (by hash) -- true if some block occurs exactly `times` times.
bool someBlockOccursExactly(const PrefixHash& ph, int n, int L, int times) {
    map<long long, int> freq;
    for (int i = 0; i + L <= n; i++) freq[ph.get(i, i + L)]++;
    for (auto& [h, c] : freq)
        if (c == times) return true;
    return false;
}
// Binary search for the largest L in 0..n-1 where the predicate is true, assuming it is true then false.
int searchLargest(int n, const function<bool(int)>& ok) {
    int lo = 0, hi = n - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (ok(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
// Brute force: try every L.
int scanLargest(int n, const function<bool(int)>& ok) {
    int best = 0;
    for (int L = 1; L < n; L++)
        if (ok(L)) best = L;
    return best;
}

int main() {
    auto repeated = [&](const string& s) {
        PrefixHash ph(s, 911382323);
        int n = s.size();
        auto ok = [&](int L) { return maxFrequency(ph, n, L) >= 2; };
        return make_pair(scanLargest(n, ok), searchLargest(n, ok));
    };
    auto p1 = repeated("banana"), p2 = repeated("abcabcabc");
    cout << "P1 brute=" << p1.first << " method=" << p1.second << "\n";
    cout << "P2 brute=" << p2.first << " method=" << p2.second << "\n";
    // N1: "some block occurs exactly twice" is true at 3, false at 1 and 2 in aaaa: not monotone.
    {
        string s = "aaaa";
        PrefixHash ph(s, 911382323);
        int n = s.size();
        auto ok = [&](int L) { return someBlockOccursExactly(ph, n, L, 2); };
        cout << "N1 brute=" << scanLargest(n, ok) << " method=" << searchLargest(n, ok) << "\n";
    }
}
