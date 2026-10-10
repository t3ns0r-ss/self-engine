#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: a + b for a = 6, b = 3. Brute: add. Method: (a xor b) + 2 (a and b).
    cout << "P1 brute=" << 6 + 3 << " method=" << (6 ^ 3) + 2 * (6 & 3) << '\n';
    // P2: is 12 a power of two? Brute: count the set bits. Method: v & (v - 1) == 0.
    cout << "P2 brute=" << (__builtin_popcount(12) == 1 ? "yes" : "no") << " method=" << ((12 & 11) == 0 ? "yes" : "no") << '\n';
    // N1: a + b = 6 and a xor b = 5 (the difference is odd); the pair built by ignoring the parity check is (0, 5).
    pair<long long, long long> built = {(6 - 5) / 2, ((6 - 5) / 2) | 5};
    bool exists = false;
    for (int a = 0; a <= 6; a++) exists |= (a ^ (6 - a)) == 5;
    cout << "N1 brute=" << (exists ? "some" : "none") << " method=" << built.first << "-" << built.second << '\n';
    // N2: a + b = 7 and a xor b = 3; the common bits (7 - 3) / 2 = 2 share the bit 1 with x = 3, which is impossible.
    pair<long long, long long> built2 = {(7 - 3) / 2, ((7 - 3) / 2) | 3};
    bool exists2 = false;
    for (int a = 0; a <= 7; a++) exists2 |= (a ^ (7 - a)) == 3;
    cout << "N2 brute=" << (exists2 ? "some" : "none") << " method=" << built2.first << "-" << built2.second << '\n';
}
