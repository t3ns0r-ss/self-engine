#include <bits/stdc++.h>
using namespace std;

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
};

// snippet:begin
// Theorem 6.3.5. How many stored numbers y have x ^ y < k? Walk the digits of x and k from the highest. Where k has a 1,
// every y in the child that makes the XOR digit 0 is below k (add its count), and the walk continues in the other child;
// where k has a 0 the walk must keep the XOR digit 0. Uses the BinaryTrie of Theorem 6.3.4.
long long countXorBelow(const BinaryTrie& t, int x, int k) {
    long long total = 0;
    int v = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        int d = x >> b & 1;
        if (k >> b & 1) {
            if (t.child[v][d]) total += t.cnt[t.child[v][d]];  // XOR digit 0 here: smaller than k whatever follows
            v = t.child[v][d ^ 1];                             // XOR digit 1 here: still equal to k so far
        } else {
            v = t.child[v][d];                                  // XOR digit must be 0 to stay equal to k so far
        }
        if (!v) break;                                         // no stored number follows this path
    }
    return total;
}
// snippet:end

int main() {
    BinaryTrie t;
    for (int y : {1, 2, 3, 4}) t.add(y, +1);
    cout << "set 1 2 3 4: x=1 k=3: " << countXorBelow(t, 1, 3) << "\n";
    cout << "set 1 2 3 4: x=0 k=3: " << countXorBelow(t, 0, 3) << "\n";
    cout << "set 1 2 3 4: x=5 k=5: " << countXorBelow(t, 5, 5) << "\n";
    cout << "set 1 2 3 4: x=5 k=0: " << countXorBelow(t, 5, 0) << "\n";
    // Check (not printed): equal to counting y with x ^ y < k, for every set of up to 4 numbers below 8 (with repeats),
    // every x below 8 and every k up to 8 (k = 8 counts every y).
    for (int a = 0; a < 8; a++)
        for (int b = -1; b < 8; b++)
            for (int c = -1; c < 8; c++)
                for (int d = -1; d < 8; d++) {
                    vector<int> values = {a};
                    for (int x : {b, c, d})
                        if (x >= 0) values.push_back(x);
                    BinaryTrie tr;
                    for (int y : values) tr.add(y, +1);
                    for (int x = 0; x < 8; x++)
                        for (int k = 0; k <= 8; k++) {
                            long long want = 0;
                            for (int y : values) want += (x ^ y) < k;
                            if (countXorBelow(tr, x, k) != want) return 1;
                        }
                }
}
