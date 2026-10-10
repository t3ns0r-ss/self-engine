#include <bits/stdc++.h>
using namespace std;

long long choose(int n, int r) {
    long long w = 1;
    for (int i = 1; i <= r; i++) w = w * (n - r + i) / i;
    return w;
}
int walk(int x, int y, bool avoid) {  // steps right and up from (x, y) to (2, 2), optionally avoiding the cell (1, 1)
    if (x > 2 || y > 2 || (avoid && x == 1 && y == 1)) return 0;
    if (x == 2 && y == 2) return 1;
    return walk(x + 1, y, avoid) + walk(x, y + 1, avoid);
}
int walk3(int x, int y) {  // steps right, up and diagonal
    if (x > 2 || y > 2) return 0;
    if (x == 2 && y == 2) return 1;
    return walk3(x + 1, y) + walk3(x, y + 1) + walk3(x + 1, y + 1);
}
int main() {
    // P1: the paths from (0, 0) to (2, 2) with right and up steps. Brute: recursion. Method: C(4, 2).
    cout << "P1 brute=" << walk(0, 0, false) << " method=" << choose(4, 2) << '\n';
    // N1: the same paths that avoid the cell (1, 1).
    cout << "N1 brute=" << walk(0, 0, true) << " method=" << choose(4, 2) << '\n';
    // N2: the same with a third kind of step, the diagonal (1, 1).
    cout << "N2 brute=" << walk3(0, 0) << " method=" << choose(4, 2) << '\n';
}
