#include <bits/stdc++.h>
using namespace std;

// A segment tree with a combining function; point set and range query.
struct Seg {
    int n;
    vector<long long> t;
    long long (*f)(long long, long long);
    long long neutral;
    Seg(const vector<long long>& a, long long (*g)(long long, long long), long long e) : n(a.size()), t(4 * a.size()), f(g), neutral(e) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<long long>& a) {
        if (lo == hi) {
            t[v] = a[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = f(t[2 * v], t[2 * v + 1]);
    }
    void set(int v, int lo, int hi, int i, long long x) {
        if (lo == hi) {
            t[v] = x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid) set(2 * v, lo, mid, i, x);
        else set(2 * v + 1, mid + 1, hi, i, x);
        t[v] = f(t[2 * v], t[2 * v + 1]);
    }
    long long query(int v, int lo, int hi, int l, int r) const {
        if (r < lo || hi < l) return neutral;
        if (l <= lo && hi <= r) return t[v];
        int mid = (lo + hi) / 2;
        return f(query(2 * v, lo, mid, l, r), query(2 * v + 1, mid + 1, hi, l, r));
    }
};
long long mn(long long x, long long y) { return min(x, y); }
long long gc(long long x, long long y) { return __gcd(x, y); }

int main() {
    // P1: a = 5 2 7 3; set a_2 to 9; minimum of positions 1..3.
    {
        vector<long long> a = {5, 2, 7, 3};
        Seg s(a, mn, LLONG_MAX);
        s.set(1, 0, 3, 1, 9), a[1] = 9;
        long long brute = min({a[0], a[1], a[2]});
        cout << "P1 brute=" << brute << " method=" << s.query(1, 0, 3, 0, 2) << "\n";
    }
    // P2: a = 12 18 8 6; set a_3 to 9; gcd of positions 2..4.
    {
        vector<long long> a = {12, 18, 8, 6};
        Seg s(a, gc, 0);
        s.set(1, 0, 3, 2, 9), a[2] = 9;
        long long brute = __gcd(__gcd(a[1], a[2]), a[3]);
        cout << "P2 brute=" << brute << " method=" << s.query(1, 0, 3, 1, 3) << "\n";
    }
    // N1: a = 3 7 2 9; how many values below 5, answered as "1 if the minimum of the range is below 5".
    {
        vector<long long> a = {3, 7, 2, 9};
        Seg s(a, mn, LLONG_MAX);
        int brute = 0;
        for (long long x : a) brute += x < 5;
        int method = s.query(1, 0, 3, 0, 3) < 5 ? 1 : 0;
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
