#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers and q questions "smallest value among positions l..r" (1-based).
Input: n q, then the n numbers, then q lines l r.
Output: the answer to each question on its own line.
*/

// snippet:begin
// Smallest value in a[l..r] (0-based, l <= r): O(n log n) build, O(1) per query.
struct RangeMin {
    vector<int> lg;          // lg[len] = the largest k with 2^k <= len
    vector<vector<int>> st;  // st[j][i] = minimum of a[i .. i + 2^j - 1]
    RangeMin(const vector<int>& a) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int len = 2; len <= n; len++) lg[len] = lg[len / 2] + 1;
        st = {a};
        for (int j = 1; (1 << j) <= n; j++) {
            st.push_back(vector<int>(n - (1 << j) + 1));
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
    int query(int l, int r) const {
        int k = lg[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    RangeMin table(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << table.query(l - 1, r - 1) << "\n";
    }
}
