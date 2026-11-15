#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.7.3. The weight of a cheapest spanning tree of the complete graph on the distinct numbers a (sorted), where the
// edge between x and y weighs x ^ y. The numbers a[lo, hi) agree on every digit above b.
long long xorMst(const vector<int>& a, int lo, int hi, int b) {
    if (hi - lo <= 1 || b < 0) return 0;
    int mid = lo;
    while (mid < hi && !(a[mid] >> b & 1)) mid++;  // a[lo, mid) has the digit 0 at b, a[mid, hi) has the digit 1
    if (mid == lo || mid == hi) return xorMst(a, lo, hi, b - 1);
    vector<array<int, 2>> child(1);  // a trie of the right part, digits b - 1 down to 0
    for (int i = mid; i < hi; i++) {
        int v = 0;
        for (int c = b - 1; c >= 0; c--) {
            int d = a[i] >> c & 1;
            if (!child[v][d]) child[v][d] = child.size(), child.push_back({0, 0});
            v = child[v][d];
        }
    }
    long long cheapest = LLONG_MAX;
    for (int i = lo; i < mid; i++) {  // the best partner of a[i]: the same digit whenever the trie has it
        int v = 0, x = 1 << b;
        for (int c = b - 1; c >= 0; c--) {
            int d = a[i] >> c & 1;
            if (!child[v][d]) d ^= 1, x |= 1 << c;
            v = child[v][d];
        }
        cheapest = min<long long>(cheapest, x);
    }
    return xorMst(a, lo, mid, b - 1) + xorMst(a, mid, hi, b - 1) + cheapest;
}
// snippet:end


long long primWith(const vector<int>& a, int (*w)(int, int)) {  // Prim's algorithm on the complete graph
    int n = a.size();
    vector<long long> dist(n, LLONG_MAX);
    vector<bool> used(n, false);
    dist[0] = 0;
    long long total = 0;
    for (int step = 0; step < n; step++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!used[i] && (u < 0 || dist[i] < dist[u])) u = i;
        used[u] = true;
        total += dist[u];
        for (int i = 0; i < n; i++)
            if (!used[i]) dist[i] = min<long long>(dist[i], w(a[u], a[i]));
    }
    return total;
}

int main() {
    auto xr = [](int x, int y) { return x ^ y; };
    auto sm = [](int x, int y) { return x + y; };
    {
        vector<int> a = {1, 2, 3, 4};
        cout << "P1 brute=" << primWith(a, xr) << " method=" << xorMst(a, 0, a.size(), 29) << "\n";
    }
    {
        vector<int> a = {3, 5, 9, 12};
        cout << "P2 brute=" << primWith(a, xr) << " method=" << xorMst(a, 0, a.size(), 29) << "\n";
    }
    {
        // N1: the weight is the sum x + y, not the XOR; the digit split no longer puts the cross edges after the inside ones.
        vector<int> a = {1, 2, 3};
        cout << "N1 brute=" << primWith(a, sm) << " method=" << xorMst(a, 0, a.size(), 29) << "\n";
    }
}
