// Builds the terms exactly in 128-bit integers (up to 38 digits) and tests each for divisibility.
// Valid for K <= 38: if a multiple exists, one appears within the first K terms.
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k;
    cin >> k;
    __int128 term = 0;
    for (int i = 1; i <= 38; i++) {
        term = term * 10 + 7;
        if (term % k == 0) {
            cout << i << "\n";
            return 0;
        }
    }
    cout << -1 << "\n";
}
