/*
Problem: for each x, print floor(sqrt(x)).
Input: q, then q integers 0 <= x <= 10^18.
Output: one line per x.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.5. floor(sqrt(x)) for 0 <= x <= 10^18.
long long isqrt(long long x) {
    long long r = sqrtl((long double)x);  // a guess, possibly off by one
    while (r > 0 && r * r > x) r--;       // too big: go down
    while ((r + 1) * (r + 1) <= x) r++;   // too small: go up
    return r;
}
// snippet:end

int main() {
    int q;
    cin >> q;
    while (q--) {
        long long x;
        cin >> x;
        cout << isqrt(x) << "\n";
    }
}
