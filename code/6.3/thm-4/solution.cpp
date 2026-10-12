#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.3.4. A binary trie of numbers below 2^BITS, written with BITS binary digits from the highest. Node 0 is the root;
// child[v][d] is the node reached by the digit d (0 = none); cnt[v] = how many stored numbers go through v.
const int BITS = 30;
struct BinaryTrie {
    vector<array<int, 2>> child = {{0, 0}};
    vector<int> cnt = {0};
    void add(int x, int delta) {  // delta = +1 stores x; delta = -1 removes one copy of x (it must be stored)
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
    int maxXor(int x) const {  // the largest x ^ y over the stored y (the trie must hold at least one number)
        int v = 0, best = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int d = x >> b & 1, opposite = child[v][d ^ 1];
            if (opposite && cnt[opposite] > 0) best |= 1 << b, v = opposite;  // a digit that differs from x gives a 1 here
            else v = child[v][d];
        }
        return best;
    }
};
// snippet:end

int main() {
    BinaryTrie t;
    for (int y : {3, 10, 5, 25, 2, 8}) t.add(y, +1);
    cout << "set 3 10 5 25 2 8: maxXor(5) = " << t.maxXor(5) << ", maxXor(8) = " << t.maxXor(8) << "\n";
    int best = 0;
    for (int y : {3, 10, 5, 25, 2, 8}) best = max(best, t.maxXor(y));
    cout << "largest XOR of two of them: " << best << "\n";
    t.add(25, -1);
    cout << "after removing 25: maxXor(5) = " << t.maxXor(5) << "\n";
    BinaryTrie one;
    one.add(7, +1);
    cout << "set 7: maxXor(7) = " << one.maxXor(7) << "\n";
    // Check (not printed): maxXor(x) equals the maximum of x ^ y over the stored y, for every set of up to 4 numbers
    // below 16 (with repeats and after removals), and every x below 16.
    for (int a = 0; a < 16; a++)
        for (int b = -1; b < 16; b++)
            for (int c = -1; c < 16; c++)
                for (int d = -1; d < 16; d++) {
                    vector<int> values = {a};
                    for (int x : {b, c, d})
                        if (x >= 0) values.push_back(x);
                    BinaryTrie tr;
                    for (int y : values) tr.add(y, +1);
                    for (int x = 0; x < 16; x++) {
                        int want = 0;
                        for (int y : values) want = max(want, x ^ y);
                        if (tr.maxXor(x) != want) return 1;
                    }
                    if (values.size() >= 2) {  // remove the last number and check again
                        tr.add(values.back(), -1);
                        values.pop_back();
                        for (int x = 0; x < 16; x++) {
                            int want = 0;
                            for (int y : values) want = max(want, x ^ y);
                            if (tr.maxXor(x) != want) return 1;
                        }
                    }
                }
}
