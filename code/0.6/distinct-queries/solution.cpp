/*
Problem: process q queries on a collection of integers: "1 x" adds x, "2 x" asks whether x is present
(YES/NO), "3" asks how many distinct values it holds.
Input: q (q <= 2*10^5), then the queries (0 <= x <= 10^9).
Output: one line per query of type 2 or 3.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    set<int> s;  // each distinct value once (Theorem 0.6.2)
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            s.insert(x);  // no effect if x is already there
        } else if (type == 2) {
            int x;
            cin >> x;
            cout << (s.count(x) ? "YES" : "NO") << "\n";
        } else {
            cout << s.size() << "\n";
        }
    }
}
