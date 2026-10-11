#include <bits/stdc++.h>
using namespace std;

// A lazy tree of sums with tags (mul, add); the same scheme as Theorem 5.3.4.
struct Lazy {
    int n;
    vector<long long> t, mul, add;
    Lazy(const vector<long long>& a) : n(a.size()), t(4 * a.size()), mul(4 * a.size(), 1), add(4 * a.size(), 0) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<long long>& a) {
        if (lo == hi) {
            t[v] = a[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    void apply(int v, int lo, int hi, long long m, long long c) {
        t[v] = m * t[v] + c * (hi - lo + 1);
        mul[v] *= m;
        add[v] = m * add[v] + c;
    }
    void push(int v, int lo, int hi) {
        int mid = (lo + hi) / 2;
        apply(2 * v, lo, mid, mul[v], add[v]);
        apply(2 * v + 1, mid + 1, hi, mul[v], add[v]);
        mul[v] = 1, add[v] = 0;
    }
    void update(int v, int lo, int hi, int l, int r, long long m, long long c) {
        if (r < lo || hi < l) return;
        if (l <= lo && hi <= r) return apply(v, lo, hi, m, c);
        push(v, lo, hi);
        int mid = (lo + hi) / 2;
        update(2 * v, lo, mid, l, r, m, c);
        update(2 * v + 1, mid + 1, hi, l, r, m, c);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    long long query(int v, int lo, int hi, int l, int r) {
        if (r < lo || hi < l) return 0;
        if (l <= lo && hi <= r) return t[v];
        push(v, lo, hi);
        int mid = (lo + hi) / 2;
        return query(2 * v, lo, mid, l, r) + query(2 * v + 1, mid + 1, hi, l, r);
    }
};

int main() {
    // P1: a = 3 1 4 1 5; add 10 to positions 2..4; sum of positions 3..5.
    {
        vector<long long> a = {3, 1, 4, 1, 5};
        Lazy s(a);
        s.update(1, 0, 4, 1, 3, 1, 10);
        for (int i = 1; i <= 3; i++) a[i] += 10;
        long long brute = a[2] + a[3] + a[4];
        cout << "P1 brute=" << brute << " method=" << s.query(1, 0, 4, 2, 4) << "\n";
    }
    // P2: a = 2 2 2 2; assign 7 to positions 2..3; sum of all.
    {
        vector<long long> a = {2, 2, 2, 2};
        Lazy s(a);
        s.update(1, 0, 3, 1, 2, 0, 7);
        a[1] = a[2] = 7;
        cout << "P2 brute=" << accumulate(a.begin(), a.end(), 0LL) << " method=" << s.query(1, 0, 3, 0, 3) << "\n";
    }
    // N1: a = 4 9; replace every value by its integer square root, applied to the stored sum (the wrong way).
    {
        vector<long long> a = {4, 9};
        long long brute = 0;
        for (long long x : a) brute += (long long)floor(sqrtl((long double)x));
        long long total = 0;
        for (long long x : a) total += x;
        long long method = (long long)floor(sqrtl((long double)total));
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
