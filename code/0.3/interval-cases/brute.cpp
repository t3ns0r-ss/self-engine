// Checks every half-integer point x/2 in a small range for membership in both intervals.
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    int pts = 0, halves = 0;  // shared integer points, shared half-unit pieces
    for (long long x = -40; x <= 40; x++)
        if (a <= x && x <= b && c <= x && x <= d) pts++;
    for (long long x = -80; x < 80; x++) {  // piece [x/2, x/2 + 1/2]
        if (2 * a <= x && x + 1 <= 2 * b && 2 * c <= x && x + 1 <= 2 * d) halves++;
    }
    if (pts == 0) cout << "DISJOINT\n";
    else if (halves == 0) cout << "TOUCH\n";
    else cout << "OVERLAP " << halves / 2 << "\n";
}
