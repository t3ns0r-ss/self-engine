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
    // P1: smallest value of a[1..5] for a = 5 2 4 7 1 3 6.
    {
        vector<int> a = {5, 2, 4, 7, 1, 3, 6};
        int brute = *min_element(a.begin() + 1, a.begin() + 6);
        SparseTable t(a, [](int x, int y) { return min(x, y); });
        cout << "P1 brute=" << brute << " method=" << t.query(1, 5) << "\n";
    }
    // P2: gcd of a[0..2] for a = 12 18 8 24 6.
    {
        vector<int> a = {12, 18, 8, 24, 6};
        int brute = 0;
        for (int i = 0; i <= 2; i++) brute = gcd(brute, a[i]);
        SparseTable t(a, [](int x, int y) { return gcd(x, y); });
        cout << "P2 brute=" << brute << " method=" << t.query(0, 2) << "\n";
    }
    // N1: sum of a[0..2] for a = 1 2 3, answered with two overlapping blocks of length 2.
    {
        vector<int> a = {1, 2, 3};
        int brute = a[0] + a[1] + a[2];
        SparseTable t(a, [](int x, int y) { return x + y; });
        cout << "N1 brute=" << brute << " method=" << t.query(0, 2) << "\n";
    }
}
