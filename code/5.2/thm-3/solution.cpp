#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.2.3. Add d to every a[l..r] and read one a[i]: a tree over the differences a[i] - a[i-1] (positions 1..n).
struct RangeAdd {
    int n;
    vector<long long> tree;  // the Fenwick tree of the difference array
    RangeAdd(int size) : n(size), tree(size + 1, 0) {}
    void addAt(int i, long long d) {
        for (; i <= n; i += i & -i) tree[i] += d;
    }
    void add(int l, int r, long long d) {  // the difference at l goes up by d, the difference at r + 1 goes down by d
        addAt(l, d);
        if (r + 1 <= n) addAt(r + 1, -d);
    }
    long long get(int i) const {  // a[i] = the sum of the differences 1..i
        long long sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
};
// snippet:end

static void show(int n, const vector<array<long long, 3>>& ops, const string& title) {
    RangeAdd t(n);
    for (auto& o : ops) t.add(o[0], o[1], o[2]);
    cout << title << ":";
    for (int i = 1; i <= n; i++) cout << ' ' << t.get(i);
    cout << "\n";
}

int main() {
    show(6, {{2, 5, 3}, {4, 6, 2}}, "n = 6, +3 on [2,5] then +2 on [4,6]");
    show(6, {{1, 6, 1}}, "n = 6, +1 on [1,6]");
    show(4, {{3, 3, 7}, {3, 3, -7}}, "n = 4, +7 on [3,3] then -7 on [3,3]");
    // Check against: adding to the array element by element, on random operations.
    mt19937 rng(5203);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 10 + 1;
        RangeAdd t(n);
        vector<long long> a(n + 1, 0);
        for (int step = 0; step < 6; step++) {
            int l = rng() % n + 1, r = l + rng() % (n - l + 1);
            long long d = (long long)(rng() % 11) - 5;
            t.add(l, r, d);
            for (int i = l; i <= r; i++) a[i] += d;
            for (int i = 1; i <= n; i++)
                if (t.get(i) != a[i]) return 1;
        }
    }
}
