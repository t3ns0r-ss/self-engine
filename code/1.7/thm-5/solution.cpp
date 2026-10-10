#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.5. a + b = (a xor b) + 2 (a and b), so from s = a + b and x = a xor b the common bits are (s - x) / 2.
// Also: the lowest set bit of v is v & -v, and v is a power of two when v & (v - 1) == 0.
pair<long long, long long> splitSumXor(long long s, long long x) {
    if (s < x || (s - x) % 2 != 0) return {-1, -1};
    long long c = (s - x) / 2;
    if (c & x) return {-1, -1};  // a bit cannot be in both and in exactly one
    return {c, c | x};           // a contains c; giving every bit of x to b makes a smallest
}
long long lowestSetBit(long long v) { return v & -v; }
bool isPowerOfTwo(long long v) { return v > 0 && (v & (v - 1)) == 0; }
// snippet:end

int main() {
    cout << "6 and 3: xor " << (6 ^ 3) << ", and " << (6 & 3) << ", sum " << 6 + 3 << " = " << (6 ^ 3) + 2 * (6 & 3) << ", or " << (6 | 3) << '\n';
    pair<long long, long long> p = splitSumXor(9, 5);
    cout << "sum 9 and xor 5: a = " << p.first << ", b = " << p.second << '\n';
    cout << "lowest set bit of 12: " << lowestSetBit(12) << '\n';
    cout << "12 is a power of two: " << (isPowerOfTwo(12) ? "yes" : "no") << ", 16: " << (isPowerOfTwo(16) ? "yes" : "no") << '\n';
    for (long long s = 0; s <= 40; s++)
        for (long long x = 0; x <= 40; x++) {
            pair<long long, long long> want = {-1, -1};
            for (long long a = 0; a <= s && want.first < 0; a++) if ((a ^ (s - a)) == x) want = {a, s - a};
            if (want != splitSumXor(s, x)) return 1;
        }
    for (long long v = 1; v <= 300; v++) {
        long long low = 1;
        while (!(v & low)) low <<= 1;
        if (low != lowestSetBit(v) || isPowerOfTwo(v) != (__builtin_popcountll(v) == 1)) return 1;
    }
}
