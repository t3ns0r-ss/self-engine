#include <bits/stdc++.h>
using namespace std;

/*
Problem: count the ranges [l, r] of an array whose gcd is 1.
Input: n, then the n numbers (1 <= a_i <= 10^9).
Output: the number of ranges.
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
// The number of ranges with gcd 1. From a fixed l the gcd only goes down as r grows (Theorem 5.1.3),
// so the first r with gcd 1 is found by binary search, and every longer range from l has gcd 1 too.
long long countGcdOne(const vector<int>& a) {
    int n = a.size();
    SparseTable t(a, [](int x, int y) { return gcd(x, y); });
    long long total = 0;  // up to n(n+1)/2, about 2*10^10
    for (int l = 0; l < n; l++) {
        int lo = l, hi = n;  // the first r with gcd 1; n means there is none
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (t.query(l, mid) == 1) hi = mid;
            else lo = mid + 1;
        }
        total += n - lo;
    }
    return total;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << countGcdOne(a) << "\n";
}
