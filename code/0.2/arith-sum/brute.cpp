// Adds the n terms one by one.
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, d, n, sum = 0;
    cin >> a >> d >> n;
    for (long long k = 0; k < n; k++) sum += a + k * d;
    cout << sum << "\n";
}
