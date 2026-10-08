#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, p;
    cin >> n >> p;
    long long last = 0, sum = 0;
    for (long long i = 1; i <= n; i++) {
        long long x = 1;
        while (i * x % p != 1) x++;  // try every candidate
        last = x;
        sum = (sum + x) % p;
    }
    cout << last << " " << sum << "\n";
}
