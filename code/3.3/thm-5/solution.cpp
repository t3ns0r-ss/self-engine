#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.5. Power-of-two splitting: c copies become bundles of 1, 2, 4, ... copies and a remainder, and choosing some of
// the bundles gives every count from 0 to c.
vector<int> bundles(int c) {
    vector<int> b;
    for (int size = 1; c > 0; size *= 2) b.push_back(min(size, c)), c -= b.back();
    return b;
}
// snippet:end

int main() {
    auto b = bundles(10);
    cout << "bundles for 10 copies:";
    for (int x : b) cout << ' ' << x;
    cout << '\n';
    for (int c = 1; c <= 200; c++) {
        auto bb = bundles(c);
        set<int> counts;
        for (int mask = 0; mask < (1 << bb.size()); mask++) {
            int s = 0;
            for (size_t i = 0; i < bb.size(); i++) if (mask >> i & 1) s += bb[i];
            counts.insert(s);
        }
        if ((int)counts.size() != c + 1 || *counts.rbegin() != c) return 1;
    }
}
