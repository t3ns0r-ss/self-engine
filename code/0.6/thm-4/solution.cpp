#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.4. The largest element <= x and the smallest element >= x of a set; -1 if there is none.
int largestAtMost(const set<int>& s, int x) {
    auto it = s.upper_bound(x);  // first element > x
    return it == s.begin() ? -1 : *prev(it);
}
int smallestAtLeast(const set<int>& s, int x) {
    auto it = s.lower_bound(x);  // first element >= x
    return it == s.end() ? -1 : *it;
}
// snippet:end

int main() {
    set<int> s = {2, 5, 9};
    cout << "set 2 5 9, largest <= 6: " << largestAtMost(s, 6) << '\n';
    cout << "set 2 5 9, smallest >= 6: " << smallestAtLeast(s, 6) << '\n';
    cout << "set 2 5 9, largest <= 1: " << largestAtMost(s, 1) << '\n';
    cout << "set 2 5 9, smallest >= 10: " << smallestAtLeast(s, 10) << '\n';
    mt19937 rng(4);
    for (int round = 0; round < 300; round++) {
        set<int> t;
        for (int i = 0; i < 6; i++) t.insert(rng() % 20);
        for (int x = -1; x <= 21; x++) {
            int lo = -1, hi = -1;
            for (int v : t) if (v <= x) lo = v;
            for (int v : t) if (v >= x) { hi = v; break; }
            if (lo != largestAtMost(t, x) || hi != smallestAtLeast(t, x)) return 1;
        }
    }
}
