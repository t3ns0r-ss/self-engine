#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1655 Maximum Xor Subarray. Given an array of n integers, print the largest XOR of a subarray.
Input: n, then the n numbers (n up to 2·10^5, values up to 10^9).
Output: the largest XOR of a (non-empty) subarray.
*/

const int BITS = 30;
struct BinaryTrie {
    vector<array<int, 2>> child = {{0, 0}};
    vector<int> cnt = {0};
    void add(int x, int delta) {
        int v = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int d = x >> b & 1;
            if (!child[v][d]) {
                child[v][d] = child.size();
                child.push_back({0, 0});
                cnt.push_back(0);
            }
            v = child[v][d];
            cnt[v] += delta;
        }
    }
    int maxXor(int x) const {
        int v = 0, best = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int d = x >> b & 1, opposite = child[v][d ^ 1];
            if (opposite && cnt[opposite] > 0) best |= 1 << b, v = opposite;
            else v = child[v][d];
        }
        return best;
    }
    long long countXorBelow(int x, int k) const {
        long long total = 0;
        int v = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int d = x >> b & 1;
            if (k >> b & 1) {
                if (child[v][d]) total += cnt[child[v][d]];
                v = child[v][d ^ 1];
            } else {
                v = child[v][d];
            }
            if (!v) break;
        }
        return total;
    }
};

// snippet:begin
// The XOR of the subarray a[l..r] is P[r + 1] ^ P[l] for the prefix XORs P (P[0] = 0). Walk the prefixes from the left: the
// best subarray ending at r uses the best earlier prefix, found in the binary trie of the earlier prefixes (Theorem 6.3.4).
// Uses the BinaryTrie of Theorem 6.3.4.
int maxSubarrayXor(const vector<int>& a) {
    BinaryTrie t;
    t.add(0, +1);  // the empty prefix P[0]
    int prefix = 0, best = 0;
    for (int x : a) {
        prefix ^= x;
        best = max(best, t.maxXor(prefix));  // the best partner among the earlier prefixes
        t.add(prefix, +1);
    }
    return best;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << maxSubarrayXor(a) << "\n";
}
