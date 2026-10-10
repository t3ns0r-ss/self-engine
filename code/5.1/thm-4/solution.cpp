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

// snippet:begin
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
// snippet:end

static void show(const vector<int>& a, int l) {
    SparseTable t(a, [](int x, int y) { return gcd(x, y); });
    auto pieces = gcdStretches(t, a.size(), l);
    cout << "a =";
    for (int x : a) cout << ' ' << x;
    cout << ", l = " << l << ":";
    for (size_t i = 0; i < pieces.size(); i++)
        cout << (i ? "," : "") << ' ' << pieces[i][0] << " on [" << pieces[i][1] << "," << pieces[i][2] << "]";
    cout << "\n";
}

int main() {
    show({12, 18, 8, 24, 6}, 0);
    show({64, 32, 16, 8, 4, 2, 1}, 0);
    cout << "the bound for 64: 1 + floor(log2 64) = " << 1 + 6 << " stretches\n";
    show({5, 5, 5}, 1);
    // Check against: the gcd of every range, and the bound 1 + floor(log2 max) on the number of stretches.
    mt19937 rng(5104);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 12 + 1, top = 1 + rng() % 1000;
        vector<int> a(n);
        for (int& x : a) x = rng() % top + 1;
        if (trial % 3 == 0)
            for (int i = 1; i < n; i++) a[i] = a[i - 1] * (1 + rng() % 2);  // long divisor chains from the other side
        int mx = *max_element(a.begin(), a.end());
        SparseTable t(a, [](int x, int y) { return gcd(x, y); });
        for (int l = 0; l < n; l++) {
            auto pieces = gcdStretches(t, n, l);
            int expectR = l, g = 0;
            for (auto& p : pieces) {
                if (p[1] != expectR) return 1;
                for (int r = p[1]; r <= p[2]; r++) {
                    g = 0;
                    for (int i = l; i <= r; i++) g = gcd(g, a[i]);
                    if (g != p[0]) return 1;
                }
                expectR = p[2] + 1;
            }
            if (expectR != n) return 1;
            if ((int)pieces.size() > 1 + (31 - __builtin_clz(mx))) return 1;
        }
    }
    // The same bound for AND and OR on values below 2^6: at most 6 changes, so at most 7 distinct values.
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 12 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 64;
        for (int l = 0; l < n; l++) {
            int andv = a[l], orv = a[l], changesAnd = 0, changesOr = 0;
            for (int r = l + 1; r < n; r++) {
                changesAnd += (andv & a[r]) != andv, andv &= a[r];
                changesOr += (orv | a[r]) != orv, orv |= a[r];
            }
            if (changesAnd > 6 || changesOr > 6) return 1;
        }
    }
}
