/*
Problem: two closed intervals [a, b] and [c, d] of the number line (a <= b, c <= d, integers).
Print DISJOINT if they share no point, TOUCH if they share exactly one point, and otherwise
OVERLAP followed by the length of the shared part.
Input: a b c d (absolute values up to 10^9).
*/
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
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << intervalCase(a, b, c, d) << "\n";
}
