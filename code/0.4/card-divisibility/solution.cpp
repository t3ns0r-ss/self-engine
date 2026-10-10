#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the multiples of 7 in [20, 100]. Brute: test every number. Method: floor(r / k) - floor((l - 1) / k).
    int count = 0;
    for (int x = 20; x <= 100; x++) count += x % 7 == 0;
    cout << "P1 brute=" << count << " method=" << 100 / 7 - 19 / 7 << '\n';
    // N1: the multiples of 3 in [0, 9] (0 is a multiple). Method: r / k - (l - 1) / k with C++ division.
    count = 0;
    for (int x = 0; x <= 9; x++) count += x % 3 == 0;
    cout << "N1 brute=" << count << " method=" << 9 / 3 - (0 - 1) / 3 << '\n';
    // N2: the numbers in 1..100 divisible by 12 or 18. Method: the two counts added.
    count = 0;
    for (int x = 1; x <= 100; x++) count += x % 12 == 0 || x % 18 == 0;
    cout << "N2 brute=" << count << " method=" << 100 / 12 + 100 / 18 << '\n';
}
