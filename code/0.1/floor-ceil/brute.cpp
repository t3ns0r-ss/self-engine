// Tries the quotients next to C++'s truncated one and keeps the one that meets the definition
// of floor (q*b <= a < (q+1)*b for b > 0), computing products in 128 bits.
#include <bits/stdc++.h>
using namespace std;
typedef __int128 i128;

int main() {
    int q;
    cin >> q;
    while (q--) {
        long long a, b;
        cin >> a >> b;
        i128 A = a, B = b;
        if (B < 0) {
            A = -A;
            B = -B;
        }
        i128 t = A / B, fl = 0, ce = 0;
        for (i128 c = t - 2; c <= t + 2; c++) {
            if (c * B <= A && A < (c + 1) * B) fl = c;        // floor
            if ((c - 1) * B < A && A <= c * B) ce = c;        // ceiling
        }
        cout << (long long)fl << " " << (long long)ce << "\n";
    }
}
