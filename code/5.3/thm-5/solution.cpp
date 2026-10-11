#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.3.5. A tree of maximums: the leftmost position with a[p] >= x, or -1 if there is none, in one walk down.
struct MaxTree {
    int n;
    vector<int> t;
    MaxTree(const vector<int>& a) : n(a.size()), t(4 * a.size(), INT_MIN) {
        for (int i = 0; i < n; i++) update(1, 0, n - 1, i, a[i]);
    }
    void update(int v, int lo, int hi, int i, int x) {  // set a[i] = x
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
        if (t[1] < x) return -1;  // not even the largest value is big enough
        int v = 1, lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (t[2 * v] >= x) v = 2 * v, hi = mid;  // the left half has a value that is big enough: the leftmost one is there
            else v = 2 * v + 1, lo = mid + 1;        // otherwise it must be in the right half
        }
        return lo;
    }
};
// snippet:end

int main() {
    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    MaxTree s(a);
    cout << "first >= 4: " << s.firstAtLeast(4) << ", first >= 5: " << s.firstAtLeast(5) << ", first >= 9: " << s.firstAtLeast(9) << ", first >= 10: " << s.firstAtLeast(10) << "\n";
    s.update(1, 0, 7, 2, 0);
    cout << "after a[2] = 0: first >= 4: " << s.firstAtLeast(4) << "\n";
    // Check against: a scan, on random arrays with random changes for every n up to 25.
    mt19937 rng(5);
    for (int n = 1; n <= 25; n++)
        for (int round = 0; round < 200; round++) {
            vector<int> b(n);
            for (auto& x : b) x = rng() % 10;
            MaxTree t(b);
            for (int op = 0; op < 10; op++) {
                int i = rng() % n, val = rng() % 10;
                t.update(1, 0, n - 1, i, val);
                b[i] = val;
                for (int x = 0; x <= 10; x++) {
                    int want = -1;
                    for (int p = 0; p < n; p++)
                        if (b[p] >= x) {
                            want = p;
                            break;
                        }
                    if (t.firstAtLeast(x) != want) return 1;
                }
            }
        }
}
