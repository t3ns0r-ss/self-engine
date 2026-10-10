/*
Problem: CSES 1071 Number Spiral. The value in row y, column x of the CSES number spiral.
Input: t (t <= 10^5), then t lines "y x" with 1 <= y, x <= 10^9.
Output: one value per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The number in row y, column x of the number spiral. Layer m = max(y, x) holds (m-1)^2 + 1 .. m^2.
long long spiral(long long y, long long x) {
    long long m = max(y, x);
    if (m % 2 == 1)  // odd layer: row m left to right, then column m upwards
        return y == m ? (m - 1) * (m - 1) + x : m * m - y + 1;
    // even layer: column m downwards, then row m right to left
    return x == m ? (m - 1) * (m - 1) + y : m * m - x + 1;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long y, x;  // the answer reaches about 10^18
        cin >> y >> x;
        cout << spiral(y, x) << "\n";
    }
}
