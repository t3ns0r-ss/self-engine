#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.7. Lattice paths with right and up steps from (x1, y1) to (x2, y2): C(dx + dy, dx), which is the choice of
// the positions of the right steps among all the steps.
long long paths(int dx, int dy) {
    if (dx < 0 || dy < 0) return 0;
    long long ways = 1;
    for (int i = 1; i <= dx; i++) ways = ways * (dy + i) / i;
    return ways;
}
// snippet:end

long long brute(int dx, int dy) {
    if (dx < 0 || dy < 0) return 0;
    if (dx == 0 && dy == 0) return 1;
    return brute(dx - 1, dy) + brute(dx, dy - 1);
}
int main() {
    cout << "paths from (0, 0) to (2, 2): " << paths(2, 2) << '\n';
    for (int a = 0; a <= 8; a++) for (int b = 0; b <= 8; b++) if (paths(a, b) != brute(a, b)) return 1;
}
