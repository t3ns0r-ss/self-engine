// Uses the library cube root.
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long c;
    cin >> c;
    long double x = cbrtl((long double)c);
    if (fabsl(x) < 5e-7L) x = 0;  // print 0.000000, not -0.000000
    printf("%.6Lf\n", x);
}
