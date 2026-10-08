#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 998244353;
    int n;
    cin >> n;
    long long num = 0, den = 1;  // the exact sum num/den
    for (int i = 0; i < n; i++) {
        long long P, Q;
        cin >> P >> Q;
        num = num * Q + P * den;
        den = den * Q;
        long long g = gcd(num, den);
        num /= g, den /= g;
    }
    // Find den^(-1) mod MOD by trying the k with (k*MOD + 1) divisible by den.
    long long inv = -1;
    for (long long k = 0; k < den; k++)
        if ((k * MOD + 1) % den == 0) {
            inv = (k * MOD + 1) / den;
            break;
        }
    cout << (num % MOD) * inv % MOD << "\n";
}
