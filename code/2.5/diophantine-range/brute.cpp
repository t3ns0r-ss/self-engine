// Brute force: test every pair (x, y) in the box (the generator keeps the box small).
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
    long long count = 0;
    for (long long x = x1; x <= x2; x++)
        for (long long y = y1; y <= y2; y++) count += a * x + b * y == c;
    cout << count << "\n";
}
