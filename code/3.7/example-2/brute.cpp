// Brute force: try every set of cut positions (a bitmask over the n - 1 gaps).
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size(), best = n;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {
        bool ok = true;
        int start = 0;
        for (int i = 0; i < n && ok; i++) {
            if (i == n - 1 || ((mask >> i) & 1)) {  // a piece ends after position i
                string piece = s.substr(start, i - start + 1);
                ok = equal(piece.begin(), piece.end(), piece.rbegin());
                start = i + 1;
            }
        }
        if (ok) best = min(best, __builtin_popcount(mask));
    }
    cout << best << "\n";
}
