#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> tree;
    Fenwick(int size) : n(size), tree(size + 1, 0) {}
    void add(int i, long long d) {
        for (; i <= n; i += i & -i) tree[i] += d;
    }
    long long prefix(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i) s += tree[i];
        return s;
    }
};

int main() {
    // P1: a = 3 1 4 1 5; add 6 at position 3; sum of positions 2..4.
    {
        vector<long long> a = {0, 3, 1, 4, 1, 5};
        Fenwick f(5);
        for (int i = 1; i <= 5; i++) f.add(i, a[i]);
        f.add(3, 6), a[3] += 6;
        long long brute = a[2] + a[3] + a[4];
        cout << "P1 brute=" << brute << " method=" << f.prefix(4) - f.prefix(1) << "\n";
    }
    // P2: n = 5 zeros; add 5 on [2, 4]; value at position 3, with a tree over the differences.
    {
        vector<long long> a(6, 0);
        for (int i = 2; i <= 4; i++) a[i] += 5;
        Fenwick f(5);
        f.add(2, 5), f.add(5, -5);
        cout << "P2 brute=" << a[3] << " method=" << f.prefix(3) << "\n";
    }
    // N1: a = 1 5 4; minimum of positions 2..3 read from the prefix minimum up to position 3.
    {
        vector<int> a = {1, 5, 4};
        int brute = min(a[1], a[2]);
        int method = *min_element(a.begin(), a.end());
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
