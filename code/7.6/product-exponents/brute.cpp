#include <bits/stdc++.h>
using namespace std;

const long long P = 1000000007;
long long powMod(long long b, long long e) {
    long long r = 1;
    for (b %= P; e > 0; e >>= 1, b = b * b % P)
        if (e & 1) r = r * b % P;
    return r;
}
int main() {
    long long n, f[40], c;
    cin >> n >> f[1] >> f[2] >> f[3] >> c;
    for (int i = 4; i <= n; i++) f[i] = powMod(c, 2 * i - 6) * f[i - 1] % P * f[i - 2] % P * f[i - 3] % P;
    cout << f[n] % P << "\n";
}
