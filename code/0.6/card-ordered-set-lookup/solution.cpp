#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1 and P2: in the set 2 5 9, the largest value <= 6 and the smallest value >= 6. Brute: scan. Method: the set.
    set<int> s = {2, 5, 9};
    int lo = -1, hi = -1;
    for (int v : s) if (v <= 6) lo = v;
    for (int v : s) if (v >= 6) { hi = v; break; }
    auto up = s.upper_bound(6), low = s.lower_bound(6);
    cout << "P1 brute=" << lo << " method=" << (up == s.begin() ? -1 : *prev(up)) << '\n';
    cout << "P2 brute=" << hi << " method=" << (low == s.end() ? -1 : *low) << '\n';
    // N1: remove one copy of 4 from the multiset 4 4 7; its size afterwards. Method: erase(4) removes every copy.
    multiset<int> a = {4, 4, 7}, b = a;
    a.erase(a.find(4));
    b.erase(4);
    cout << "N1 brute=" << a.size() << " method=" << b.size() << '\n';
    // N2: the largest value <= 5 in 2 5 9, taken as the element before lower_bound(5).
    auto lb = s.lower_bound(5);
    cout << "N2 brute=" << 5 << " method=" << *prev(lb) << '\n';
}
