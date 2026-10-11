#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers; q operations: "1 l r x" sets every number in l..r to x, "2 l r" asks for the sum of l..r.
Input: n q, the n numbers, then q operations (1-based).
Output: one line per operation of the second kind.
*/

// snippet:begin
// Range assign and range sum with blocks of B positions. If asg[b] is set, the whole block b holds the value val[b]
// and a[] is out of date for it; a partial change first writes that value into a[] (push), then changes single positions.
struct AssignBlocks {
    int n, B;
    vector<long long> a, sum, val;
    vector<char> asg;
    AssignBlocks(const vector<long long>& v, int block) : n(v.size()), B(block), a(v), sum((v.size() + block - 1) / block, 0), val(sum), asg(sum.size(), 0) {
        for (int i = 0; i < n; i++) sum[i / B] += a[i];
    }
    int lo(int b) const { return b * B; }
    int hi(int b) const { return min(n, (b + 1) * B) - 1; }
    void push(int b) {
        if (!asg[b]) return;
        for (int i = lo(b); i <= hi(b); i++) a[i] = val[b];
        asg[b] = 0;
    }
    void assign(int l, int r, long long x) {
        for (int b = l / B; b <= r / B; b++) {
            if (l <= lo(b) && hi(b) <= r) asg[b] = 1, val[b] = x, sum[b] = x * (hi(b) - lo(b) + 1);  // the whole block at once
            else {
                push(b);
                for (int i = max(l, lo(b)); i <= min(r, hi(b)); i++) sum[b] += x - a[i], a[i] = x;  // one position at a time
            }
        }
    }
    long long query(int l, int r) {
        long long s = 0;
        for (int b = l / B; b <= r / B; b++) {
            if (l <= lo(b) && hi(b) <= r) s += sum[b];
            else {
                push(b);
                for (int i = max(l, lo(b)); i <= min(r, hi(b)); i++) s += a[i];
            }
        }
        return s;
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    AssignBlocks blocks(a, max(1, (int)sqrt((double)n)));
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            long long x;
            cin >> x;
            blocks.assign(l - 1, r - 1, x);
        } else {
            cout << blocks.query(l - 1, r - 1) << "\n";
        }
    }
}
