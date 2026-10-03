// Checks every integer in [a, b] (the generator keeps b - a small).
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, x;
    cin >> a >> b >> x;
    long long cnt = 0;
    for (long long v = a; v <= b; v++)
        if (v % x == 0) cnt++;
    cout << cnt << "\n";
}
