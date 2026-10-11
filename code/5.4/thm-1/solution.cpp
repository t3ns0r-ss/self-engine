#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.4.1. Blocks of B positions. sum[b] is the true sum of block b; add[b] is an addition given to the whole block
// that is already counted in sum[b] but not in a[i].
struct Blocks {
    int n, B;
    vector<long long> a, sum, add;
    Blocks(const vector<long long>& v, int block) : n(v.size()), B(block), a(v), sum((v.size() + block - 1) / block, 0), add(sum) {
        for (int i = 0; i < n; i++) sum[i / B] += a[i];
    }
    int end(int b) const { return min(n, (b + 1) * B) - 1; }  // last position of block b
    void addRange(int l, int r, long long x) {
        for (int i = l; i <= r;) {
            int b = i / B;
            if (i == b * B && end(b) <= r) add[b] += x, sum[b] += x * (end(b) - i + 1), i = end(b) + 1;  // a whole block
            else a[i] += x, sum[b] += x, i++;                                                            // one position
        }
    }
    long long rangeSum(int l, int r) const {
        long long s = 0;
        for (int i = l; i <= r;) {
            int b = i / B;
            if (i == b * B && end(b) <= r) s += sum[b], i = end(b) + 1;
            else s += a[i] + add[b], i++;
        }
        return s;
    }
};
// snippet:end

int main() {
    vector<long long> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    Blocks b(v, 3);
    cout << "blocks:";
    for (long long s : b.sum) cout << ' ' << s;
    cout << "\n";
    b.addRange(2, 8, 10);
    cout << "after +10 on [2..8]: whole blocks 1 and 2 got the tag:";
    for (long long t : b.add) cout << ' ' << t;
    cout << "\n";
    cout << "sum[1..9] = " << b.rangeSum(1, 9) << ", sum[3..5] = " << b.rangeSum(3, 5) << ", sum[0..0] = " << b.rangeSum(0, 0) << "\n";
    // Check against: a plain array, on random operations, for several block sizes and every n up to 30.
    mt19937 rng(9);
    for (int n = 1; n <= 30; n++)
        for (int block : {1, 2, 3, 5, 7})
            for (int round = 0; round < 40; round++) {
                vector<long long> w(n);
                for (auto& x : w) x = (long long)(rng() % 21) - 10;
                Blocks t(w, block);
                for (int op = 0; op < 20; op++) {
                    int l = rng() % n, r = rng() % n;
                    if (l > r) swap(l, r);
                    if (rng() % 2) {
                        long long x = (long long)(rng() % 21) - 10;
                        t.addRange(l, r, x);
                        for (int i = l; i <= r; i++) w[i] += x;
                    } else {
                        long long want = 0;
                        for (int i = l; i <= r; i++) want += w[i];
                        if (t.rangeSum(l, r) != want) return 1;
                    }
                }
            }
}
