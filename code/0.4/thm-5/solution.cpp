#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.4.5 (Euclid). gcd(a, b) = gcd(b, a mod b); the loop ends when b reaches 0.
long long gcdLL(long long a, long long b) { return b == 0 ? a : gcdLL(b, a % b); }
// snippet:end

int main() {
    cout << "gcd(1071, 462) = " << gcdLL(1071, 462) << '\n';
    cout << "gcd(17, 5) = " << gcdLL(17, 5) << '\n';
    cout << "gcd(0, 9) = " << gcdLL(0, 9) << '\n';
    for (int a = 0; a <= 60; a++)
        for (int b = 0; b <= 60; b++) {
            int best = 0;  // the definition: the largest common divisor (gcd(0, 0) is 0)
            for (int d = 1; d <= 60; d++)
                if (a % d == 0 && b % d == 0) best = d;
            if (a == 0 && b == 0) best = 0;
            if (gcdLL(a, b) != best) return 1;
        }
}
