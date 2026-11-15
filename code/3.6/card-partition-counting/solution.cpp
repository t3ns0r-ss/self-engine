#include <bits/stdc++.h>
using namespace std;

long long ordered(int n, const vector<int>& parts) {
    vector<long long> f(n + 1, 0);
    f[0] = 1;
    for (int m = 1; m <= n; m++) for (int p : parts) if (p <= m) f[m] += f[m - p];
    return f[n];
}
long long unordered(int n, const vector<int>& parts) {
    vector<long long> f(n + 1, 0);
    f[0] = 1;
    for (int p : parts) for (int m = p; m <= n; m++) f[m] += f[m - p];
    return f[n];
}
int main() {
    // P1: the compositions of 4 with parts 1 2 3 (ordered). P2: the partitions (unordered). Brute: recursion on the first part.
    long long ord = 0, unord = 0;
    function<void(int, int, bool)> go = [&](int left, int minPart, bool orderMatters) {
        if (left == 0) { (orderMatters ? ord : unord)++; return; }
        for (int p = orderMatters ? 1 : minPart; p <= 3 && p <= left; p++) go(left - p, p, orderMatters);
    };
    go(4, 1, true);
    go(4, 1, false);
    cout << "P1 brute=" << ord << " method=" << ordered(4, {1, 2, 3}) << '\n';
    cout << "P2 brute=" << unord << " method=" << unordered(4, {1, 2, 3}) << '\n';
    // N1: the ways to write 4 with the parts 1 2 3, each part used at most once, computed as compositions.
    int once = 0;
    for (int mask = 0; mask < 8; mask++) {
        int s = 0;
        for (int i = 0; i < 3; i++) if (mask >> i & 1) s += i + 1;
        once += s == 4;
    }
    cout << "N1 brute=" << once << " method=" << ordered(4, {1, 2, 3}) << '\n';
    // N2: split 6 candies among 3 children, each at least one (exactly 3 parts), computed as compositions of 6 with parts 1..6.
    int exact = 0;
    for (int a = 1; a <= 6; a++) for (int b = 1; b <= 6; b++) { int c = 6 - a - b; exact += c >= 1; }
    cout << "N2 brute=" << exact << " method=" << ordered(6, {1, 2, 3, 4, 5, 6}) << '\n';
}
