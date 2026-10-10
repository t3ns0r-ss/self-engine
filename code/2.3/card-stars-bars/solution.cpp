#include <bits/stdc++.h>
using namespace std;

long long choose(int n, int r) {
    if (r < 0 || r > n) return 0;
    long long w = 1;
    for (int i = 1; i <= r; i++) w = w * (n - r + i) / i;
    return w;
}
int main() {
    // P1: 7 identical candies for 3 children. Brute: all triples. Method: C(7 + 2, 2).
    int brute = 0;
    for (int a = 0; a <= 7; a++) for (int b = 0; a + b <= 7; b++) brute++;
    cout << "P1 brute=" << brute << " method=" << choose(9, 2) << '\n';
    // N1: the same, but each child gets at most 3 candies; the method ignores the limit.
    int limited = 0;
    for (int a = 0; a <= 3; a++) for (int b = 0; b <= 3; b++) { int c = 7 - a - b; limited += c >= 0 && c <= 3; }
    cout << "N1 brute=" << limited << " method=" << choose(9, 2) << '\n';
    // N2: 3 different candies for 2 children, counted as identical items: C(3 + 1, 1).
    cout << "N2 brute=" << 8 << " method=" << choose(4, 1) << '\n';
}
