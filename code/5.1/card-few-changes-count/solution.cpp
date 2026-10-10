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
    // P1: the number of different gcd values of a[0..r] over r, for a = 12 18 8 24 6.
    {
        vector<int> a = {12, 18, 8, 24, 6};
        int brute = 0, g = 0, last = -1;
        for (int x : a) {
            g = gcd(g, x);
            brute += g != last;
            last = g;
        }
        SparseTable t(a, [](int x, int y) { return gcd(x, y); });
        cout << "P1 brute=" << brute << " method=" << gcdStretches(t, a.size(), 0).size() << "\n";
    }
    // P2: the sum of the gcd of all subarrays of 6 4 2 8.
    {
        vector<int> a = {6, 4, 2, 8};
        int n = a.size();
        long long brute = 0, method = 0;
        for (int l = 0; l < n; l++) {
            int g = 0;
            for (int r = l; r < n; r++) brute += g = gcd(g, a[r]);
        }
        SparseTable t(a, [](int x, int y) { return gcd(x, y); });
        for (int l = 0; l < n; l++)
            for (auto& p : gcdStretches(t, n, l)) method += (long long)p[0] * (p[2] - p[1] + 1);
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    // N1: stretches of the XOR of a[0..r] for a = 1 2 1 2 1 2 1 2; the log bound (1 + floor(log2 max) = 2) would promise at most 2.
    {
        vector<int> a = {1, 2, 1, 2, 1, 2, 1, 2};
        int brute = 0, v = 0, last = -1;
        for (int x : a) {
            v ^= x;
            brute += v != last;
            last = v;
        }
        cout << "N1 brute=" << brute << " method=" << 1 + (31 - __builtin_clz(*max_element(a.begin(), a.end()))) << "\n";
    }
}
