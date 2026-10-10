#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: how many groups of 3 are needed for 7 people. Brute: add people to a group until all are placed.
    int a = 7, b = 3, groups = 0;
    for (int placed = 0; placed < a; placed += b) groups++;
    cout << "P1 brute=" << groups << " method=" << (a + b - 1) / b << '\n';
    // N1: the ceiling of -6 / 4 (that is -1.5). Brute: the smallest integer q with 4q >= -6. Method: (a + b - 1) / b.
    a = -6, b = 4;
    int q = -100;
    while (q * b < a) q++;
    cout << "N1 brute=" << q << " method=" << (a + b - 1) / b << '\n';
    // N2: the integer square root of 10^18 - 1. Brute: integer comparisons. Method: sqrt on a double, cut off.
    long long x = 999999999999999999LL, s = 999999990LL;
    while ((s + 1) * (s + 1) <= x) s++;
    cout << "N2 brute=" << s << " method=" << (long long)sqrt((double)x) << '\n';
}
