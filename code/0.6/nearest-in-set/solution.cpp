/*
Problem: a multiset of integers under q queries: "1 x" adds x, "2 x" removes one copy of x (present),
"3 x" prints the largest element <= x, "4 x" the smallest element >= x (or -1 if none).
Input: q (q <= 2*10^5), then the queries (0 <= x <= 10^9).
Output: one line per query of type 3 or 4.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    multiset<int> s;
    while (q--) {
        int type, x;
        cin >> type >> x;
        if (type == 1) {
            s.insert(x);
        } else if (type == 2) {
            s.erase(s.find(x));  // one copy; s.erase(x) would remove every copy
        } else if (type == 3) {
            auto it = s.upper_bound(x);  // first element > x (Theorem 0.6.4)
            if (it == s.begin()) cout << -1 << "\n";
            else cout << *prev(it) << "\n";  // the element before it is the largest <= x
        } else {
            auto it = s.lower_bound(x);  // first element >= x
            if (it == s.end()) cout << -1 << "\n";
            else cout << *it << "\n";
        }
    }
}
