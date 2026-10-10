#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the sum of 200000 values of 10^9, in long long (method) against exact 128-bit arithmetic (brute).
    long long sum = 0;
    __int128 exact = 0;
    for (int i = 0; i < 200000; i++) sum += 1000000000, exact += 1000000000;
    cout << "P1 brute=" << (long long)exact << " method=" << sum << '\n';
    // N1: the price "0.29" in cents. Brute: read the digits as an integer. Method: double times 100, cut off.
    volatile double price = 0.29;
    long long cents = 0;
    for (char ch : string("029")) cents = cents * 10 + (ch - '0');
    cout << "N1 brute=" << cents << " method=" << (long long)(price * 100) << '\n';
}
