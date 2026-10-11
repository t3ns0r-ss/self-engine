#include <bits/stdc++.h>
using namespace std;

struct MaxTree {
    int n;
    vector<int> t;
    MaxTree(const vector<int>& a) : n(a.size()), t(4 * a.size()) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<int>& a) {
        if (lo == hi) {
            t[v] = a[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = max(t[2 * v], t[2 * v + 1]);
    }
    void update(int v, int lo, int hi, int i, int x) {
        if (lo == hi) {
            t[v] = x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid) update(2 * v, lo, mid, i, x);
        else update(2 * v + 1, mid + 1, hi, i, x);
        t[v] = max(t[2 * v], t[2 * v + 1]);
    }
    int firstAtLeast(int x) const {
        if (t[1] < x) return -1;
        int v = 1, lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (t[2 * v] >= x) v = 2 * v, hi = mid;
            else v = 2 * v + 1, lo = mid + 1;
        }
        return lo;
    }
};
int bruteFirst(const vector<int>& a, int x) {
    for (int i = 0; i < (int)a.size(); i++)
        if (a[i] >= x) return i;
    return -1;
}

int main() {
    {
        vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
        MaxTree s(a);
        cout << "P1 brute=" << bruteFirst(a, 5) << " method=" << s.firstAtLeast(5) << "\n";
    }
    {
        vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
        MaxTree s(a);
        s.update(1, 0, 7, 2, 0), a[2] = 0;
        cout << "P2 brute=" << bruteFirst(a, 4) << " method=" << s.firstAtLeast(4) << "\n";
    }
    {
        vector<int> a = {3, 1, 5};
        MaxTree s(a);
        int brute = -1;
        for (int i = 0; i < 3; i++)
            if (a[i] == 4) {
                brute = i;
                break;
            }
        cout << "N1 brute=" << brute << " method=" << s.firstAtLeast(4) << "\n";
    }
}
