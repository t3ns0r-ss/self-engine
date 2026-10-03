/*
Problem: two closed intervals [a, b] and [c, d] of the number line (a <= b, c <= d, integers).
Print DISJOINT if they share no point, TOUCH if they share exactly one point, and otherwise
OVERLAP followed by the length of the shared part.
Input: a b c d (absolute values up to 10^9).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    long long lo = max(a, c), hi = min(b, d);  // the shared part is [lo, hi] if lo <= hi
    if (lo > hi) cout << "DISJOINT\n";          // case 1: nothing shared
    else if (lo == hi) cout << "TOUCH\n";       // case 2: one point (also when an interval is a point)
    else cout << "OVERLAP " << hi - lo << "\n";  // case 3: a segment of positive length
}
