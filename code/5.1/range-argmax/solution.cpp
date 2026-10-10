#include <bits/stdc++.h>
using namespace std;

/*
Problem: n towers and q questions "which tower in positions l..r is the tallest (the leftmost one if tied)?" (1-based).
Input: n q, then the n heights, then q lines l r.
Output: the position of the answer for each question.
*/

// snippet:begin
// Position of the leftmost maximum in a[l..r] (0-based): O(n log n) build, O(1) per query.
struct RangeArgMax {
    vector<int> a, lg;
    vector<vector<int>> st;  // st[j][i] = position of the leftmost maximum of a[i .. i + 2^j - 1]
    int better(int x, int y) const {  // the taller tower; on a tie the smaller position (a total order, so overlap is harmless)
        return a[x] > a[y] || (a[x] == a[y] && x < y) ? x : y;
    }
    RangeArgMax(const vector<int>& values) : a(values) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int len = 2; len <= n; len++) lg[len] = lg[len / 2] + 1;
        st.push_back(vector<int>(n));
        iota(st[0].begin(), st[0].end(), 0);
        for (int j = 1; (1 << j) <= n; j++) {
            st.push_back(vector<int>(n - (1 << j) + 1));
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = better(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
    int query(int l, int r) const {
        int k = lg[r - l + 1];
        return better(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    RangeArgMax table(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << table.query(l - 1, r - 1) + 1 << "\n";
    }
}
