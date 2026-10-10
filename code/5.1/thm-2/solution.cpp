#include <bits/stdc++.h>
using namespace std;

// snippet:begin
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
// snippet:end

int main() {
    auto gcdOp = [](int x, int y) { return gcd(x, y); };
    auto andOp = [](int x, int y) { return x & y; };
    auto plusOp = [](int x, int y) { return x + y; };
    {
        SparseTable t({12, 18, 8, 24, 6}, gcdOp);
        cout << "gcd of 12 18 8 24 6 over [0,2] = " << t.query(0, 2) << "\n";
        cout << "gcd of 12 18 8 24 6 over [1,4] = " << t.query(1, 4) << "\n";
    }
    {
        SparseTable t({14, 13, 11, 7}, andOp);
        cout << "and of 14 13 11 7 over [0,2] = " << t.query(0, 2) << "\n";
    }
    {
        SparseTable t({7, 3, 9}, [](int x, int y) { return max(x, y); });
        cout << "max of 7 3 9 over [1,1] = " << t.query(1, 1) << "\n";
    }
    {
        SparseTable t({1, 2, 3}, plusOp);
        cout << "two blocks with + on 1 2 3 over [0,2]: " << t.query(0, 2) << ", true sum " << 1 + 2 + 3 << "\n";
    }
    // Check against: folding the operation over the range, on every array of length 1..6 over {1..4}.
    vector<function<int(int, int)>> ops = {
        [](int x, int y) { return min(x, y); }, [](int x, int y) { return max(x, y); }, gcdOp, andOp,
        [](int x, int y) { return x | y; }};
    for (auto& op : ops)
        for (int n = 1; n <= 6; n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= 4;
            for (int code = 0; code < total; code++) {
                vector<int> a(n);
                for (int i = 0, c = code; i < n; i++, c /= 4) a[i] = c % 4 + 1;
                SparseTable t(a, op);
                for (int l = 0; l < n; l++) {
                    int fold = a[l];
                    for (int r = l; r < n; r++) {
                        if (r > l) fold = op(fold, a[r]);
                        if (t.query(l, r) != fold) return 1;
                    }
                }
            }
        }
}
