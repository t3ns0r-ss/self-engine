#include <bits/stdc++.h>
using namespace std;

/*
Problem: AtCoder Educational DP Contest, task W, Intervals. A string of N bits (each 0 or 1) is chosen. There are M intervals
(l_i, r_i, a_i): if the string has at least one 1 among the positions l_i..r_i, the reward a_i (possibly negative) is added. Print the
largest total reward over all strings. (N, M up to 2·10^5, |a_i| up to 10^9.)
Input: N and M, then M lines "l r a".
*/

// Theorem 7.3.4: range add, range maximum (the add at a node is not pushed down).
struct AddMax {
    vector<long long> mx, add;
    AddMax(int n) : mx(4 * n, 0), add(4 * n, 0) {}
    void update(int v, int lo, int hi, int l, int r, long long x) {
        if (r < lo || hi < l) return;
        if (l <= lo && hi <= r) { mx[v] += x, add[v] += x; return; }
        int mid = (lo + hi) / 2;
        update(2 * v, lo, mid, l, r, x), update(2 * v + 1, mid + 1, hi, l, r, x);
        mx[v] = max(mx[2 * v], mx[2 * v + 1]) + add[v];
    }
    long long query(int v, int lo, int hi, int l, int r) {
        if (r < lo || hi < l) return LLONG_MIN / 2;
        if (l <= lo && hi <= r) return mx[v];
        int mid = (lo + hi) / 2;
        return max(query(2 * v, lo, mid, l, r), query(2 * v + 1, mid + 1, hi, l, r)) + add[v];
    }
};

// snippet:begin
// Theorem 7.3.4: f[j] = the best total when the last 1 so far is at position j (0: none). A 1 at position i starts the state i from the
// best state before it; an interval (l, r, a) with r = i adds a to the states l..i (their last 1 lies inside the interval).
long long bestString(int n, vector<array<long long, 3>> intervals) {
    sort(intervals.begin(), intervals.end(), [](auto& x, auto& y) { return x[1] < y[1]; });
    AddMax f(n + 1);
    size_t p = 0;
    for (int i = 1; i <= n; i++) {
        f.update(1, 0, n, i, i, f.query(1, 0, n, 0, i - 1));
        for (; p < intervals.size() && intervals[p][1] == i; p++) f.update(1, 0, n, intervals[p][0], i, intervals[p][2]);
    }
    return f.query(1, 0, n, 0, n);
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> intervals(m);
    for (auto& iv : intervals) cin >> iv[0] >> iv[1] >> iv[2];
    cout << bestString(n, intervals) << "\n";
}
