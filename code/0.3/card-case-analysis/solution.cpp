#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: [1, 5] and [3, 8]: the length of the shared part. Brute: count the shared integer points, minus one.
    // Method: min(b, d) - max(a, c).
    int shared = 0;
    for (int x = 0; x <= 10; x++) shared += 1 <= x && x <= 5 && 3 <= x && x <= 8;
    cout << "P1 brute=" << shared - 1 << " method=" << min(5, 8) - max(1, 3) << '\n';
    // P2: [1, 3] and [3, 6]: the same quantity.
    shared = 0;
    for (int x = 0; x <= 10; x++) shared += 1 <= x && x <= 3 && 3 <= x && x <= 6;
    cout << "P2 brute=" << shared - 1 << " method=" << min(3, 6) - max(1, 3) << '\n';
    // N1: the number of shared points of [1, 3] and [3, 6] when the case "lo == hi" is forgotten (lo >= hi is
    // treated as disjoint).
    int lo = max(1, 3), hi = min(3, 6);
    cout << "N1 brute=" << shared << " method=" << (lo >= hi ? 0 : hi - lo + 1) << '\n';
    // N2: the sign of a * b with the cases "both positive or both negative: +" and "otherwise: -", for a = 0, b = 5.
    int a = 0, b = 5;
    int sign = (a > 0) - (a < 0), truth = (long long)a * b > 0 ? 1 : (long long)a * b < 0 ? -1 : 0;
    int rule = ((a > 0 && b > 0) || (a < 0 && b < 0)) ? 1 : -1;
    (void)sign;
    cout << "N2 brute=" << truth << " method=" << rule << '\n';
}
