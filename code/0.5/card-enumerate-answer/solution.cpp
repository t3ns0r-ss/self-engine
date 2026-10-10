#include <bits/stdc++.h>
using namespace std;

int digitSum(int x) {
    int s = 0;
    for (; x > 0; x /= 10) s += x % 10;
    return s;
}

int main() {
    // P1: the smallest x in 1..100 divisible by 7 with digit sum 10. Brute: the multiples of 7 in order. Method: test every x.
    int brute = -1, method = -1;
    for (int x = 7; x <= 100 && brute < 0; x += 7) if (digitSum(x) == 10) brute = x;
    for (int x = 1; x <= 100 && method < 0; x++) if (x % 7 == 0 && digitSum(x) == 10) method = x;
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the smallest x with x * x >= 50. Brute: the integer square root of 49, plus one. Method: test every x.
    int s = 0;
    while ((s + 1) * (s + 1) <= 49) s++;
    method = -1;
    for (int x = 1; x <= 100 && method < 0; x++) if (x * x >= 50) method = x;
    cout << "P2 brute=" << s + 1 << " method=" << method << '\n';
    // N1: the smallest x with x * x >= 10^18, testing x up to 10^6 only (what a time limit allows).
    long long r = 1000000000LL;
    method = -1;
    for (long long x = 1; x <= 1000000 && method < 0; x++) if (x * x >= 1000000000000000000LL) method = x;
    cout << "N1 brute=" << r << " method=" << method << '\n';
    // N2: the smallest x with digit sum 40, testing x up to 9999.
    brute = -1;
    for (int x = 1; x <= 100000 && brute < 0; x++) if (digitSum(x) == 40) brute = x;
    method = -1;
    for (int x = 1; x <= 9999 && method < 0; x++) if (digitSum(x) == 40) method = x;
    cout << "N2 brute=" << brute << " method=" << method << '\n';
}
