#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: subsets of {3, 5, 7} with sum in [8, 12]. Brute: three yes/no choices written out. Method: bitmasks.
    int a[3] = {3, 5, 7}, brute = 0, method = 0;
    for (int x = 0; x < 2; x++) for (int y = 0; y < 2; y++) for (int z = 0; z < 2; z++) { int s = x * 3 + y * 5 + z * 7; brute += 8 <= s && s <= 12; }
    for (int mask = 0; mask < 8; mask++) { int s = 0; for (int i = 0; i < 3; i++) if (mask >> i & 1) s += a[i]; method += 8 <= s && s <= 12; }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the subsets of 4 items. Brute: recursion on yes/no. Method: 1 << 4.
    function<int(int)> rec = [&](int i) { return i == 4 ? 1 : rec(i + 1) + rec(i + 1); };
    cout << "P2 brute=" << rec(0) << " method=" << (1 << 4) << '\n';
    // N1: each of 2 items goes to place A, B or C. Brute: 3 * 3 assignments. Method: one bit per item (2 * 2).
    cout << "N1 brute=" << 3 * 3 << " method=" << (1 << 2) << '\n';
    // N2: the number of orders of 3 items. Brute: 3!. Method: the 2^3 subsets.
    cout << "N2 brute=" << 6 << " method=" << (1 << 3) << '\n';
}
