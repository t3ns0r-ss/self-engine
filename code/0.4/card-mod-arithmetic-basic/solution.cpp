#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: 123 * 456 mod 7. Brute: the exact product, then the remainder. Method: reduce the factors first.
    cout << "P1 brute=" << 123 * 456 % 7 << " method=" << (123 % 7) * (456 % 7) % 7 << '\n';
    // N1: (10 / 2) mod 6. Method: reduce 10 first, then divide: (10 mod 6) / 2.
    cout << "N1 brute=" << (10 / 2) % 6 << " method=" << (10 % 6) / 2 << '\n';
    // N2: (3 - 5) mod 7 as a value in [0, 7). Method: (a - b) % m without correcting the sign.
    cout << "N2 brute=" << ((3 - 5) % 7 + 7) % 7 << " method=" << (3 - 5) % 7 << '\n';
}
