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

int kth(const Fenwick& f, long long k) {
    int pos = 0, step = 1;
    while (step * 2 <= f.n) step *= 2;
    for (; step > 0; step /= 2)
        if (pos + step <= f.n && f.tree[pos + step] < k) {
            pos += step;
            k -= f.tree[pos];
        }
    return pos + 1;
}

int main() {
    // P1: places 2, 3, 5, 8 of 8 present; the place of the 3rd.
    {
        Fenwick f(8);
        for (int p : {2, 3, 5, 8}) f.add(p, 1);
        cout << "P1 brute=" << 5 << " method=" << kth(f, 3) << "\n";
    }
    // P2: list 10 20 30 40; remove the element at place 2 twice; the second removed value.
    {
        vector<int> v = {10, 20, 30, 40};
        v.erase(v.begin() + 1);
        int brute = v[1];
        Fenwick f(4);
        for (int p = 1; p <= 4; p++) f.add(p, 1);
        int first = kth(f, 2);
        f.add(first, -1);
        int second = kth(f, 2);
        cout << "P2 brute=" << brute << " method=" << 10 * second << "\n";
    }
    // N1: list 5 6; insert 7 at place 2; element at place 3, against the 3rd smallest of the values.
    {
        vector<int> v = {5, 6};
        v.insert(v.begin() + 1, 7);
        int brute = v[2];
        vector<int> sorted = v;
        sort(sorted.begin(), sorted.end());
        cout << "N1 brute=" << brute << " method=" << sorted[2] << "\n";
    }
}
