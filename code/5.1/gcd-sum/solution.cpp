#include <bits/stdc++.h>
using namespace std;

/*
Problem: the sum of gcd(a[l..r]) over all ranges l <= r.
Input: n, then the n numbers (1 <= a_i <= 10^6).
Output: the sum (up to about 2*10^10 ranges times 10^6, so 64-bit).
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
// The sum of the gcd over all ranges. For each l the gcd takes few values, each over a stretch of r (Theorem 5.1.4);
// the end of a stretch is the first r where the gcd drops below the current value (Theorem 5.1.3).
long long sumOfGcds(const vector<int>& a) {
    int n = a.size();
    SparseTable t(a, [](int x, int y) { return gcd(x, y); });
    long long total = 0;
    for (int l = 0; l < n; l++) {
        int r = l;
        while (r < n) {
            int g = t.query(l, r);
            int lo = r, hi = n;  // the first position where the gcd is below g; n means there is none
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (t.query(l, mid) < g) hi = mid;
                else lo = mid + 1;
            }
            total += (long long)g * (lo - r);  // the gcd is g on r .. lo-1
            r = lo;
        }
    }
    return total;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << sumOfGcds(a) << "\n";
}
