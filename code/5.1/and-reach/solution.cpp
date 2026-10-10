#include <bits/stdc++.h>
using namespace std;

/*
Problem: for each question (l, k), the largest r >= l such that a[l] & a[l+1] & ... & a[r] >= k, or -1 if a[l] < k.
Input: n q, then the n numbers, then q lines l k (positions are 1-based).
Output: the answer to each question.
*/

// Theorem 5.1.2. Sparse table for an operation that does not change when a value is counted twice (min, max, gcd, AND, OR).
struct SparseTable {
    function<int(int, int)> op;
    vector<int> lg;  // lg[len] = the largest k with 2^k <= len
    vector<vector<int>> st;  // st[j][i] = a[i] op ... op a[i + 2^j - 1]
    SparseTable(const vector<int>& a, function<int(int, int)> op_) : op(op_) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int len = 2; len <= n; len++) lg[len] = lg[len / 2] + 1;
        st = {a};
        for (int j = 1; (1 << j) <= n; j++) {
            st.push_back(vector<int>(n - (1 << j) + 1));
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
    int query(int l, int r) const {  // a[l] op ... op a[r], with 0 <= l <= r < n
        int k = lg[r - l + 1];
        return op(st[k][l], st[k][r - (1 << k) + 1]);  // two blocks of length 2^k that may overlap
    }
};

// snippet:begin
// The largest r (0-based) with a[l] & ... & a[r] >= k, or -1. The AND only loses bits as r grows (Theorem 5.1.3),
// so "AND < k" is false and then true: find the first r where it is true and step back one.
int farthest(const SparseTable& t, int n, int l, int k) {
    int lo = l, hi = n;  // the first r with AND < k; n means there is none
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (t.query(l, mid) < k) hi = mid;
        else lo = mid + 1;
    }
    return lo - 1 < l ? -1 : lo - 1;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    SparseTable t(a, [](int x, int y) { return x & y; });
    while (q--) {
        int l, k;
        cin >> l >> k;
        int r = farthest(t, n, l - 1, k);
        cout << (r < 0 ? -1 : r + 1) << "\n";
    }
}
