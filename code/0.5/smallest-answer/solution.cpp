/*
Problem: the smallest x with 1 <= x <= 10^6 whose digit sum is S and which is a multiple of K, or -1.
Input: S K (1 <= S <= 60, 1 <= K <= 10^6).
Output: x or -1.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.5.5. The smallest x in 1..10^6 that is a multiple of k and has digit sum s, or -1.
int digitSum(int x) {
    int s = 0;
    for (; x > 0; x /= 10) s += x % 10;
    return s;
}

int smallestAnswer(int s, int k) {
    for (int x = 1; x <= 1000000; x++)  // the first x that passes is the smallest
        if (x % k == 0 && digitSum(x) == s) return x;
    return -1;
}
// snippet:end

int main() {
    int s, k;
    cin >> s >> k;
    cout << smallestAnswer(s, k) << "\n";
}
