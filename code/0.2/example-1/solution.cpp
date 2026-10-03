/*
Problem: CSES 1071 Number Spiral. The value in row y, column x of the CSES number spiral.
Input: t (t <= 10^5), then t lines "y x" with 1 <= y, x <= 10^9.
Output: one value per line.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long y, x;  // the answer reaches about 10^18
        cin >> y >> x;
        long long m = max(y, x);  // the cell lies on layer m, whose numbers are (m-1)^2 + 1 .. m^2
        long long ans;
        if (m % 2 == 1) {
            // odd layer: row m left to right, then column m upwards
            if (y == m) ans = (m - 1) * (m - 1) + x;
            else ans = m * m - y + 1;
        } else {
            // even layer: column m downwards, then row m right to left
            if (x == m) ans = (m - 1) * (m - 1) + y;
            else ans = m * m - x + 1;
        }
        cout << ans << "\n";
    }
}
