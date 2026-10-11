#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers; q operations: "1 k x" sets a_k = x, "2 l r lo hi" asks how many of a_l..a_r lie between lo and hi (both included).
Input: n q, the n numbers, then q operations (1-based).
Output: one line per operation of the second kind.
*/

// snippet:begin
// Blocks of B positions, each with a sorted copy of its values. A change fixes one copy; a count uses a binary search per whole block.
struct SortedBlocks {
    int n, B;
    vector<int> a;
    vector<vector<int>> sorted;
    SortedBlocks(const vector<int>& v, int block) : n(v.size()), B(block), a(v), sorted((v.size() + block - 1) / block) {
        for (int i = 0; i < n; i++) sorted[i / B].push_back(a[i]);
        for (auto& s : sorted) sort(s.begin(), s.end());
    }
    void set(int i, int x) {
        auto& s = sorted[i / B];
        s.erase(lower_bound(s.begin(), s.end(), a[i]));  // take out one copy of the old value
        s.insert(upper_bound(s.begin(), s.end(), x), x);  // put the new value in its place
        a[i] = x;
    }
    int countBetween(int l, int r, int lo, int hi) const {  // positions l..r with lo <= a[i] <= hi
        int cnt = 0;
        for (int i = l; i <= r;) {
            int b = i / B, last = min(n, (b + 1) * B) - 1;
            if (i == b * B && last <= r) {
                const auto& s = sorted[b];
                cnt += upper_bound(s.begin(), s.end(), hi) - lower_bound(s.begin(), s.end(), lo), i = last + 1;
            } else cnt += lo <= a[i] && a[i] <= hi, i++;
        }
        return cnt;
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    SortedBlocks blocks(a, max(1, (int)sqrt((double)n)));
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, x;
            cin >> k >> x;
            blocks.set(k - 1, x);
        } else {
            int l, r, lo, hi;
            cin >> l >> r >> lo >> hi;
            cout << blocks.countBetween(l - 1, r - 1, lo, hi) << "\n";
        }
    }
}
