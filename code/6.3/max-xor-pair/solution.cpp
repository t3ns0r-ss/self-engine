#include <bits/stdc++.h>
using namespace std;

/*
Problem: the largest XOR of two different elements (different places) of an array.
Input: n (at least 2), then n numbers below 2^30.
Output: the largest value of a_i XOR a_j over i != j.
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
// The largest a_i ^ a_j over i < j: insert the numbers one by one, and before inserting a number ask for its best partner
// among the numbers inserted so far (Theorem 6.3.4). Uses the BinaryTrie of Theorem 6.3.4.
int largestPairXor(const vector<int>& a) {
    BinaryTrie t;
    t.add(a[0], +1);
    int best = 0;
    for (size_t i = 1; i < a.size(); i++) {
        best = max(best, t.maxXor(a[i]));
        t.add(a[i], +1);
    }
    return best;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << largestPairXor(a) << "\n";
}
