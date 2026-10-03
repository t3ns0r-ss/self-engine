/*
Problem: CSES 1068 Weird Algorithm. Starting from n, halve it if even, else replace it by 3n + 1,
until it reaches 1; print every value.
Input: n (1 <= n <= 10^6).
Output: the values, separated by spaces.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;  // the values climb above 2^31 for some starting n below 10^6
    cin >> n;
    cout << n;
    while (n != 1) {
        if (n % 2 == 0) n /= 2;
        else n = 3 * n + 1;
        cout << " " << n;
    }
    cout << "\n";
}
