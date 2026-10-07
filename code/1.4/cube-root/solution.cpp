/*
Problem: for an integer c, print the real number x with x * x * x = c, to 6 digits after the point.
Input: c (|c| <= 10^18).
Output: x with 6 digits after the decimal point.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long c;
    cin >> c;
    // f(x) = x^3 is increasing, so "x^3 >= c" is false...true on the reals (Theorem 1.4.5).
    long double lo = -1e6 - 1, hi = 1e6 + 1;  // (10^6)^3 = 10^18 bounds every answer
    for (int it = 0; it < 100; it++) {          // a fixed number of halvings, not a while on eps
        long double mid = (lo + hi) / 2;
        if (mid * mid * mid >= c) hi = mid;
        else lo = mid;
    }
    printf("%.6Lf\n", hi);
}
