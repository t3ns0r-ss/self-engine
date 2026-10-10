#include <bits/stdc++.h>
using namespace std;

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
// Theorem 5.1.3. The first r >= l whose aggregate a[l] op ... op a[r] satisfies reached(), or -1 if there is none.
// Needs: once reached() is true for some r, it stays true for every larger r (min, max, gcd, AND, OR).
int firstRight(const SparseTable& t, int n, int l, function<bool(int)> reached) {
    int lo = l, hi = n;  // the answer is in [lo, hi]; hi = n stands for "none"
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (reached(t.query(l, mid))) hi = mid;  // true at mid: the answer is mid or earlier
        else lo = mid + 1;                       // false at mid: the answer is later
    }
    return lo == n ? -1 : lo;
}
// snippet:end

int main() {
    auto minOp = [](int x, int y) { return min(x, y); };
    auto maxOp = [](int x, int y) { return max(x, y); };
    auto gcdOp = [](int x, int y) { return gcd(x, y); };
    auto andOp = [](int x, int y) { return x & y; };
    auto orOp = [](int x, int y) { return x | y; };
    {
        vector<int> a = {6, 9, 4, 3, 8, 1};
        SparseTable t(a, minOp);
        cout << "min of 6 9 4 3 8 1 from l=0, first r with min <= 3: " << firstRight(t, a.size(), 0, [](int v) { return v <= 3; }) << "\n";
        cout << "same array, first r with min <= 0: " << firstRight(t, a.size(), 0, [](int v) { return v <= 0; }) << "\n";
    }
    {
        vector<int> a = {15, 14, 12, 8, 7};
        SparseTable t(a, andOp);
        cout << "and of 15 14 12 8 7 from l=0, first r with and < 12: " << firstRight(t, a.size(), 0, [](int v) { return v < 12; }) << "\n";
        cout << "and of 15 14 12 8 7 from l=3, first r with and < 8: " << firstRight(t, a.size(), 3, [](int v) { return v < 8; }) << "\n";
    }
    {
        vector<int> a = {12, 18, 8, 24, 6};
        SparseTable t(a, gcdOp);
        cout << "gcd of 12 18 8 24 6 from l=0, first r with gcd <= 2: " << firstRight(t, a.size(), 0, [](int v) { return v <= 2; }) << "\n";
    }
    // Check against: a left-to-right scan, for every array of length 1..5 over {1..4}, every l and every threshold.
    // min, gcd and AND never go up as r grows (the test is aggregate <= x); max and OR never go down (aggregate >= x).
    struct Case { function<int(int, int)> op; bool down; };
    vector<Case> cases = {{minOp, true}, {gcdOp, true}, {andOp, true}, {maxOp, false}, {orOp, false}};
    for (auto& c : cases)
        for (int n = 1; n <= 5; n++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= 4;
            for (int code = 0; code < total; code++) {
                vector<int> a(n);
                for (int i = 0, k = code; i < n; i++, k /= 4) a[i] = k % 4 + 1;
                SparseTable t(a, c.op);
                for (int l = 0; l < n; l++)
                    for (int x = 0; x <= 8; x++) {
                        auto reached = [&](int v) { return c.down ? v <= x : v >= x; };
                        int want = -1, fold = 0;
                        for (int r = l; r < n && want < 0; r++) {
                            fold = r == l ? a[r] : c.op(fold, a[r]);
                            if (reached(fold)) want = r;
                        }
                        if (firstRight(t, n, l, reached) != want) return 1;
                    }
            }
        }
}
