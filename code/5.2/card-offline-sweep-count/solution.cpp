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
    // P1: distinct values of a[2..5] for a = 1 2 1 3 2, by the sweep with last occurrences.
    {
        vector<int> a = {1, 2, 1, 3, 2};
        Fenwick f(5);
        map<int, int> last;
        for (int r = 1; r <= 5; r++) {
            if (last.count(a[r - 1])) f.add(last[a[r - 1]], -1);
            last[a[r - 1]] = r;
            f.add(r, 1);
        }
        set<int> s(a.begin() + 1, a.begin() + 5);
        cout << "P1 brute=" << s.size() << " method=" << f.prefix(5) - f.prefix(1) << "\n";
    }
    // P2: elements of positions 2..4 that are at most 3, for a = 5 1 4 2 3, by inserting positions in the order of the values.
    {
        vector<int> a = {5, 1, 4, 2, 3};
        int brute = 0;
        for (int i = 1; i <= 3; i++) brute += a[i] <= 3;
        vector<int> order = {0, 1, 2, 3, 4};
        sort(order.begin(), order.end(), [&](int x, int y) { return a[x] < a[y]; });
        Fenwick f(5);
        for (int p : order)
            if (a[p] <= 3) f.add(p + 1, 1);
        cout << "P2 brute=" << brute << " method=" << f.prefix(4) - f.prefix(1) << "\n";
    }
    // N1: a = 1 2 1; the marks for r = 3 are built, then a_2 becomes 1; distinct values of positions 1..3.
    {
        vector<int> a = {1, 2, 1};
        Fenwick f(3);
        map<int, int> last;
        for (int r = 1; r <= 3; r++) {
            if (last.count(a[r - 1])) f.add(last[a[r - 1]], -1);
            last[a[r - 1]] = r;
            f.add(r, 1);
        }
        a[1] = 1;
        set<int> s(a.begin(), a.end());
        cout << "N1 brute=" << s.size() << " method=" << f.prefix(3) - f.prefix(0) << "\n";
    }
}
