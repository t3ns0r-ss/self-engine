#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.1. The largest value of a b-bit signed type, and a product computed in 64 bits.
unsigned long long maxSigned(int b) { return (1ULL << (b - 1)) - 1; }
long long product(int a, int b) { return 1LL * a * b; }
// snippet:end

int main() {
    cout << "largest 32-bit signed value: " << maxSigned(32) << '\n';
    cout << "largest 64-bit signed value: " << maxSigned(64) << '\n';
    cout << "100000 * 100000 computed in 64 bits: " << product(100000, 100000) << '\n';
    if (maxSigned(32) != (unsigned long long)numeric_limits<int>::max()) return 1;
    if (maxSigned(64) != (unsigned long long)numeric_limits<long long>::max()) return 1;
    for (int a = -300; a <= 300; a += 7)
        for (int b = -300; b <= 300; b += 11)
            if (product(a, b) != (long long)((__int128)a * b)) return 1;
}
