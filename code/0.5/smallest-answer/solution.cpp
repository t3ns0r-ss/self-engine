/*
Problem: the smallest x with 1 <= x <= 10^6 whose digit sum is S and which is a multiple of K, or -1.
Input: S K (1 <= S <= 60, 1 <= K <= 10^6).
Output: x or -1.
*/
#include <bits/stdc++.h>
using namespace std;

int digitSum(int x) {
    int s = 0;
    for (; x > 0; x /= 10) s += x % 10;
    return s;
}

int main() {
    int s, k;
    cin >> s >> k;
    for (int x = 1; x <= 1000000; x++)  // the first x that passes is the smallest (Theorem 0.5.5)
        if (x % k == 0 && digitSum(x) == s) {
            cout << x << "\n";
            return 0;
        }
    cout << -1 << "\n";
}
