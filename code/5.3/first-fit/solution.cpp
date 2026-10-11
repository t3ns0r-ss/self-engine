#include <bits/stdc++.h>
using namespace std;

/*
Problem: a hotel has n rooms with free[i] free beds. q groups arrive; group j needs g_j beds in one room and takes the first room with
at least g_j free beds (and its free beds drop by g_j), or 0 if there is none.
Input: n q, the n numbers free[i], then the q numbers g_j.
Output: the room (1-based) for each group, separated by spaces.
*/

// snippet:begin
// A tree of maximums over the free beds. The walk down finds the first room with at least g beds, or 0 if there is none.
struct Hotel {
    int n;
    vector<long long> t;
    Hotel(const vector<long long>& a) : n(a.size()), t(4 * a.size()) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<long long>& a) {
        if (lo == hi) {
            t[v] = a[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = max(t[2 * v], t[2 * v + 1]);
    }
    int take(long long g) {  // the room (1-based) where the group goes, 0 if none; the beds are used up
        if (t[1] < g) return 0;  // even the roomiest room is too small
        int v = 1, lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (t[2 * v] >= g) v = 2 * v, hi = mid;  // the first fitting room is in the left half
            else v = 2 * v + 1, lo = mid + 1;
        }
        t[v] -= g;
        for (v /= 2; v >= 1; v /= 2) t[v] = max(t[2 * v], t[2 * v + 1]);  // fix the path above the leaf
        return lo + 1;
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    Hotel hotel(a);
    for (int j = 0; j < q; j++) {
        long long g;
        cin >> g;
        cout << hotel.take(g) << (j + 1 < q ? ' ' : '\n');
    }
}
