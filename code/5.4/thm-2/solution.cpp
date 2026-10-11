#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.4.2. Blocks of B positions, each with a sorted copy of its values.
struct SortedBlocks {
    int n, B;
    vector<int> a;
    vector<vector<int>> sorted;
    SortedBlocks(const vector<int>& v, int block) : n(v.size()), B(block), a(v), sorted((v.size() + block - 1) / block) {
        for (int i = 0; i < n; i++) sorted[i / B].push_back(a[i]);
        for (auto& s : sorted) sort(s.begin(), s.end());
    }
    int countLess(int l, int r, int x) const {  // positions l..r with a[i] < x
        int cnt = 0;
        for (int i = l; i <= r;) {
            int b = i / B, last = min(n, (b + 1) * B) - 1;
            if (i == b * B && last <= r) cnt += lower_bound(sorted[b].begin(), sorted[b].end(), x) - sorted[b].begin(), i = last + 1;
            else cnt += a[i] < x, i++;
        }
        return cnt;
    }
    void set(int i, int x) {  // replace one value: fix the sorted copy of its block
        auto& s = sorted[i / B];
        s.erase(lower_bound(s.begin(), s.end(), a[i]));
        s.insert(upper_bound(s.begin(), s.end(), x), x);
        a[i] = x;
    }
};
// snippet:end

int main() {
    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    SortedBlocks s(v, 3);
    cout << "block copies:";
    for (auto& b : s.sorted) {
        cout << " [";
        for (size_t i = 0; i < b.size(); i++) cout << (i ? " " : "") << b[i];
        cout << "]";
    }
    cout << "\n";
    cout << "less than 5 in [1..7] = " << s.countLess(1, 7, 5) << "\n";
    s.set(4, 0);
    cout << "after a[4] = 0: less than 5 in [1..7] = " << s.countLess(1, 7, 5) << ", less than 5 in [3..5] = " << s.countLess(3, 5, 5) << "\n";
    // Check against: counting by a loop, on random operations, for several block sizes and every n up to 30.
    mt19937 rng(4);
    for (int n = 1; n <= 30; n++)
        for (int block : {1, 2, 3, 5, 7})
            for (int round = 0; round < 40; round++) {
                vector<int> w(n);
                for (auto& x : w) x = rng() % 10;
                SortedBlocks t(w, block);
                for (int op = 0; op < 20; op++) {
                    if (rng() % 2) {
                        int i = rng() % n, x = rng() % 10;
                        t.set(i, x);
                        w[i] = x;
                    } else {
                        int l = rng() % n, r = rng() % n, x = rng() % 11;
                        if (l > r) swap(l, r);
                        int want = 0;
                        for (int i = l; i <= r; i++) want += w[i] < x;
                        if (t.countLess(l, r, x) != want) return 1;
                    }
                }
            }
}
