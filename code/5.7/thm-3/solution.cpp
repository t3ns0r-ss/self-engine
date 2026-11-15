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

long long prim(const vector<int>& a) {  // the reference: Prim's algorithm on the complete graph
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
            if (!used[i]) dist[i] = min<long long>(dist[i], a[u] ^ a[i]);
    }
    return total;
}

long long solve(vector<int> a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());  // equal numbers are joined by weight 0 edges
    return xorMst(a, 0, a.size(), 29);
}

int main() {
    for (vector<int> a : {vector<int>{1, 2, 3, 4}, vector<int>{5, 6, 7}, vector<int>{0, 8}, vector<int>{4, 4, 4}}) {
        for (int x : a) cout << x << " ";
        cout << "-> " << solve(a) << "\n";
    }
    // Check (not printed): the tree weight equals Prim's on every list of up to 5 numbers below 8, repeats included.
    for (int len = 1; len <= 5; len++) {
        int total = 1;
        for (int i = 0; i < len; i++) total *= 8;
        for (int code = 0; code < total; code++) {
            vector<int> a;
            for (int i = 0, c = code; i < len; i++, c /= 8) a.push_back(c % 8);
            if (solve(a) != prim(a)) return 1;
        }
    }
}
