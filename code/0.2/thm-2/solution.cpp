#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.2.2. All divisors of n in increasing order; d is tried only up to sqrt(n).
vector<long long> divisors(long long n) {
    vector<long long> small, large;  // d <= sqrt(n), and their partners n / d
    for (long long d = 1; d * d <= n; d++) {
        if (n % d != 0) continue;
        small.push_back(d);
        if (d != n / d) large.push_back(n / d);  // a square root is recorded once
    }
    small.insert(small.end(), large.rbegin(), large.rend());
    return small;
}
// snippet:end

int main() {
    for (long long n : {12LL, 36LL, 97LL}) {
        cout << "divisors of " << n << ":";
        for (long long d : divisors(n)) cout << ' ' << d;
        cout << '\n';
    }
    for (long long n = 1; n <= 400; n++) {
        vector<long long> all;
        for (long long d = 1; d <= n; d++)
            if (n % d == 0) all.push_back(d);
        if (all != divisors(n)) return 1;
    }
}
