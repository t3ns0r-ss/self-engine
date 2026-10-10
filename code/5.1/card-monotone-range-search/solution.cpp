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

// Theorem 5.1.4. For a fixed l: the stretches of r on which gcd(a[l..r]) stays the same, as {value, first r, last r}.
vector<array<int, 3>> gcdStretches(const SparseTable& t, int n, int l) {
    vector<array<int, 3>> pieces;
    int r = l;
    while (r < n) {
        int g = t.query(l, r);
        int next = firstRight(t, n, l, [&](int v) { return v < g; });  // first r where the gcd drops below g
        if (next == -1) next = n;
        pieces.push_back({g, r, next - 1});
        r = next;
    }
    return pieces;
}

int main() {
    auto firstScan = [](const vector<int>& a, int l, function<int(int, int)> op, function<bool(int)> reached) {
        int v = a[l];
        for (int r = l; r < (int)a.size(); r++) {
            if (r > l) v = op(v, a[r]);
            if (reached(v)) return r;
        }
        return -1;
    };
    // P1: first r >= 0 with min(a[0..r]) <= 3 for a = 6 9 4 3 8 1.
    {
        vector<int> a = {6, 9, 4, 3, 8, 1};
        auto op = [](int x, int y) { return min(x, y); };
        auto reached = [](int v) { return v <= 3; };
        SparseTable t(a, op);
        cout << "P1 brute=" << firstScan(a, 0, op, reached) << " method=" << firstRight(t, a.size(), 0, reached) << "\n";
    }
    // P2: first r >= 0 with OR(a[0..r]) >= 7 for a = 1 2 4 8.
    {
        vector<int> a = {1, 2, 4, 8};
        auto op = [](int x, int y) { return x | y; };
        auto reached = [](int v) { return v >= 7; };
        SparseTable t(a, op);
        cout << "P2 brute=" << firstScan(a, 0, op, reached) << " method=" << firstRight(t, a.size(), 0, reached) << "\n";
    }
    // N1: first r >= 0 with XOR(a[0..r]) >= 3 for a = 3 1 2 5. XOR is not monotone, so a binary search on r (with the XOR of
    // the prefix computed directly) goes wrong.
    {
        vector<int> a = {3, 1, 2, 5};
        int n = a.size();
        auto xorTo = [&](int r) {
            int v = 0;
            for (int i = 0; i <= r; i++) v ^= a[i];
            return v;
        };
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (xorTo(mid) >= 3) hi = mid;
            else lo = mid + 1;
        }
        auto op = [](int x, int y) { return x ^ y; };
        cout << "N1 brute=" << firstScan(a, 0, op, [](int v) { return v >= 3; }) << " method=" << (lo == n ? -1 : lo) << "\n";
    }
}
