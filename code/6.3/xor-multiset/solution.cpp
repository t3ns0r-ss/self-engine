#include <bits/stdc++.h>
using namespace std;

/*
Problem: a multiset that starts with the number 0, and q operations: "+ x" adds x, "- x" removes one copy of x (it is
present), "? x" asks for the largest x XOR y over the numbers y in the multiset.
Input: q, then q lines with the sign and the number (below 2^30).
Output: the answer to each "?" on its own line.
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
// The operations on a multiset of numbers: the counts of the binary trie allow removals (Theorem 6.3.4, note 2). Uses the
// BinaryTrie of Theorem 6.3.4; the multiset starts with 0, so a question always has an answer.
vector<int> runOperations(const vector<pair<char, int>>& operations) {
    BinaryTrie t;
    t.add(0, +1);
    vector<int> answers;
    for (auto [sign, x] : operations) {
        if (sign == '+') t.add(x, +1);
        else if (sign == '-') t.add(x, -1);
        else answers.push_back(t.maxXor(x));
    }
    return answers;
}
// snippet:end

int main() {
    int q;
    cin >> q;
    vector<pair<char, int>> operations(q);
    for (auto& [sign, x] : operations) cin >> sign >> x;
    for (int a : runOperations(operations)) cout << a << "\n";
}
