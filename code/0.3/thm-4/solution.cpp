#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.3.4. Three cases cover every pair of integer intervals [a, b] and [c, d].
string intervalCase(long long a, long long b, long long c, long long d) {
    long long lo = max(a, c), hi = min(b, d);  // the shared part is [lo, hi] if lo <= hi
    if (lo > hi) return "DISJOINT";            // case 1: nothing shared
    if (lo == hi) return "TOUCH";              // case 2: one point (also when an interval is a point)
    return "OVERLAP " + to_string(hi - lo);    // case 3: a segment of positive length
}
// snippet:end

int main() {
    cout << "[1, 5] and [3, 8]: " << intervalCase(1, 5, 3, 8) << '\n';
    cout << "[1, 3] and [3, 6]: " << intervalCase(1, 3, 3, 6) << '\n';
    cout << "[1, 2] and [4, 6]: " << intervalCase(1, 2, 4, 6) << '\n';
    for (int a = 0; a <= 6; a++)  // every pair of intervals inside 0..6 against counting the shared integer points
        for (int b = a; b <= 6; b++)
            for (int c = 0; c <= 6; c++)
                for (int d = c; d <= 6; d++) {
                    int shared = 0;
                    for (int x = 0; x <= 6; x++) shared += a <= x && x <= b && c <= x && x <= d;
                    string want = shared == 0 ? "DISJOINT" : shared == 1 ? "TOUCH" : "OVERLAP " + to_string(shared - 1);
                    if (intervalCase(a, b, c, d) != want) return 1;
                }
}
