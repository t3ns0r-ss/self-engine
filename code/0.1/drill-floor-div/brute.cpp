#include <bits/stdc++.h>
using namespace std;

// Brute force for small values: step q until b*q <= a < b*(q+1).
int main() {
    int queries;
    cin >> queries;
    while (queries--) {
        long long a, b;
        cin >> a >> b;
        long long q = -1000;
        while (b * (q + 1) <= a) q++;
        cout << q << " " << a - b * q << "\n";
    }
}
