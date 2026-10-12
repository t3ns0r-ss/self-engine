#include <bits/stdc++.h>
using namespace std;

/*
Problem: count the pairs i < j with a_i XOR a_j < k.
Input: n, k, then n numbers below 2^30 (k below 2^30).
Output: the number of pairs.
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
// The number of pairs i < j with a_i ^ a_j < k: each number is counted against the numbers inserted before it, then inserted
// (inserting first would pair a number with itself, whose XOR is 0). Theorem 6.3.5. Uses the BinaryTrie of Theorem 6.3.4.
long long countPairsBelow(const vector<int>& a, int k) {
    BinaryTrie t;
    long long pairs = 0;
    for (int x : a) {
        pairs += t.countXorBelow(x, k);
        t.add(x, +1);
    }
    return pairs;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << countPairsBelow(a, k) << "\n";
}
