// Builds the root bit by bit from the top (2^30 is above sqrt(10^18)), keeping a bit when the
// square, computed in 128 bits, stays at most x.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        long long x;
        cin >> x;
        long long r = 0;
        for (int bit = 30; bit >= 0; bit--) {
            __int128 c = r + (1LL << bit);
            if (c * c <= x) r += 1LL << bit;
        }
        cout << r << "\n";
    }
}
