#include <bits/stdc++.h>
using namespace std;

/*
Problem: n daily sales; q operations: "1 k d" adds d to the sales of day k, "2 a b" asks for the total of days a..b.
Input: n q, the n numbers, then q operations (days are 1-based).
Output: one line per operation of the second kind.
*/

// snippet:begin
// A Fenwick tree of sums over positions 1..n: add to one position, sum of a prefix, sum of a range.
struct Fenwick {
    int n;
    vector<long long> tree;  // 64-bit: sums can pass 2*10^9
    Fenwick(int size) : n(size), tree(size + 1, 0) {}
    void add(int i, long long d) {
        for (; i <= n; i += i & -i) tree[i] += d;  // the blocks that contain position i
    }
    long long prefix(int i) const {
        long long sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];  // the blocks that make up positions 1..i
        return sum;
    }
    long long range(int l, int r) const { return prefix(r) - prefix(l - 1); }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    Fenwick f(n);
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        f.add(i, x);
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long d;
            cin >> k >> d;
            f.add(k, d);
        } else {
            int a, b;
            cin >> a >> b;
            cout << f.range(a, b) << "\n";
        }
    }
}
