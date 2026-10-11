#include <bits/stdc++.h>
using namespace std;

/*
Problem: a row of n lamps with brightness a_i; q operations: "1 l r d" adds d to the brightness of lamps l..r,
"2 k" asks for the brightness of lamp k.
Input: n q, the n numbers, then q operations (1-based).
Output: one line per operation of the second kind.
*/

// snippet:begin
// Add d to a[l..r] and read one a[k]: a Fenwick tree over the differences a[i] - a[i-1] (positions 1..n).
struct RangeAdd {
    int n;
    vector<long long> tree;
    RangeAdd(int size) : n(size), tree(size + 1, 0) {}
    void addAt(int i, long long d) {
        for (; i <= n; i += i & -i) tree[i] += d;
    }
    void add(int l, int r, long long d) {
        addAt(l, d);                  // the difference at l rises by d
        if (r + 1 <= n) addAt(r + 1, -d);  // the difference just after r falls by d
    }
    long long get(int k) const {  // a[k] = the sum of the differences 1..k (the start values are added by the caller)
        long long sum = 0;
        for (; k > 0; k -= k & -k) sum += tree[k];
        return sum;
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> start(n + 1);
    for (int i = 1; i <= n; i++) cin >> start[i];
    RangeAdd t(n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            long long d;
            cin >> l >> r >> d;
            t.add(l, r, d);
        } else {
            int k;
            cin >> k;
            cout << start[k] + t.get(k) << "\n";
        }
    }
}
