#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers and a number k <= n. Cut the sequence into exactly k non-empty consecutive parts. The value of a part is the number
of different numbers in it. Print the largest total value.
Input: n and k, then the n numbers.
Output: the largest total value.
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
// Theorem 7.3.4 once for each part: prev[j] = the best value of the first j numbers in c - 1 parts. In round c, f[j] = prev[j] + the
// number of different values in a[j..i); moving to the next i adds 1 to every j at or after the previous occurrence of that value.
long long bestSplit(const vector<int>& a, int k) {
    int n = a.size();
    const long long NEG = -1e15;
    vector<long long> prev(n + 1, NEG), cur;
    prev[0] = 0;
    for (int c = 1; c <= k; c++) {
        AddMax f(n + 1);
        for (int j = 0; j <= n; j++) f.update(1, 0, n, j, j, prev[j]);
        map<int, int> last;  // position (from 1) of the previous occurrence of a value, 0 if none
        cur.assign(n + 1, NEG);
        for (int i = 1; i <= n; i++) {
            f.update(1, 0, n, last[a[i - 1]], i - 1, 1);
            last[a[i - 1]] = i;
            cur[i] = f.query(1, 0, n, 0, i - 1);
        }
        prev = cur;
    }
    return prev[n];
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << bestSplit(a, k) << "\n";
}
