#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.4.6. lcm(a, b) = a / gcd(a, b) * b (divide first), and the numbers in 1..n divisible by a or b.
long long gcdLL(long long a, long long b) { return b == 0 ? a : gcdLL(b, a % b); }
long long lcmLL(long long a, long long b) { return a / gcdLL(a, b) * b; }
long long divisibleByEither(long long n, long long a, long long b) { return n / a + n / b - n / lcmLL(a, b); }
// snippet:end

int main() {
    cout << "lcm(12, 18) = " << lcmLL(12, 18) << '\n';
    cout << "lcm(4, 6) = " << lcmLL(4, 6) << '\n';
    cout << "numbers in 1..100 divisible by 12 or 18: " << divisibleByEither(100, 12, 18) << '\n';
    for (int a = 1; a <= 20; a++)
        for (int b = 1; b <= 20; b++) {
            int l = 1;  // the definition: the smallest positive common multiple
            while (l % a != 0 || l % b != 0) l++;
            if (lcmLL(a, b) != l) return 1;
            int count = 0;
            for (int x = 1; x <= 100; x++) count += x % a == 0 || x % b == 0;
            if (divisibleByEither(100, a, b) != count) return 1;
        }
}
