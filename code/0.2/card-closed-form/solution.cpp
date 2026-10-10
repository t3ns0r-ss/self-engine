#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: 1 + 2 + ... + 100000. Brute: the loop. Method: n (n + 1) / 2.
    long long n = 100000, loop = 0;
    for (long long k = 1; k <= n; k++) loop += k;
    cout << "P1 brute=" << loop << " method=" << n * (n + 1) / 2 << '\n';
    // N1: 1 + ... + 5 with the halving done first: (n / 2) * (n + 1).
    n = 5, loop = 0;
    for (long long k = 1; k <= n; k++) loop += k;
    cout << "N1 brute=" << loop << " method=" << (n / 2) * (n + 1) << '\n';
    // N2: the sum of the array 3 1 4 1 5, which has no pattern. Method: n (first + last) / 2.
    vector<int> a = {3, 1, 4, 1, 5};
    int sum = 0;
    for (int x : a) sum += x;
    cout << "N2 brute=" << sum << " method=" << a.size() * (a.front() + a.back()) / 2 << '\n';
}
