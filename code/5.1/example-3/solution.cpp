#include <bits/stdc++.h>
using namespace std;

/*
Problem (LeetCode 1521, Find a Value of a Mysterious Function Closest to Target): func(arr, l, r) is the AND of arr[l..r];
find the smallest |func(arr, l, r) - target| over all 0 <= l <= r < n.
Input: n target, then the n numbers (1 <= arr[i] <= 10^6, 0 <= target <= 10^7).
Output: the smallest difference.
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
// The smallest |AND(arr[l..r]) - target|. For each l the AND takes at most 20 different values, each over a stretch of r
// (Theorem 5.1.4); the end of a stretch is the first r where the AND drops below the current value (Theorem 5.1.3).
int closestAnd(const vector<int>& arr, int target) {
    int n = arr.size(), best = INT_MAX;
    SparseTable t(arr, [](int x, int y) { return x & y; });
    for (int l = 0; l < n; l++) {
        int r = l;
        while (r < n) {
            int v = t.query(l, r);
            best = min(best, abs(v - target));
            int lo = r, hi = n;  // the first position where the AND is below v; n means there is none
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (t.query(l, mid) < v) hi = mid;
                else lo = mid + 1;
            }
            r = lo;
        }
    }
    return best;
}
// snippet:end

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> arr(n);
    for (int& x : arr) cin >> x;
    cout << closestAnd(arr, target) << "\n";
}
