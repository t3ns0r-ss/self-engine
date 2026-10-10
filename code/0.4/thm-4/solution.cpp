#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.4.4. Reduce after every operation: a * b mod m and n! mod m without ever forming the huge numbers.
long long mulMod(long long a, long long b, long long m) { return (a % m) * (b % m) % m; }

long long factorialMod(long long n, long long m) {
    long long r = 1 % m;
    for (long long i = 2; i <= n; i++) r = mulMod(r, i, m);
    return r;
}
// snippet:end

int main() {
    cout << "123 * 456 mod 7 = " << mulMod(123, 456, 7) << '\n';
    cout << "5! mod 7 = " << factorialMod(5, 7) << '\n';
    cout << "20! mod 1000000007 = " << factorialMod(20, 1000000007) << '\n';
    for (int m = 1; m <= 30; m++) {
        long long exact = 1;
        for (int n = 0; n <= 15; n++) {
            if (n > 0) exact *= n;
            if (factorialMod(n, m) != exact % m) return 1;
        }
    }
}
