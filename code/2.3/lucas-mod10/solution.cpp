/*
Problem: LeetCode 2221, Find Triangular Sum of an Array (idea only, with n allowed up to 10^5).
Input: n, then n digits.
Output: the single digit left after repeating "replace the array by the sums of neighbours modulo 10".
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The last digit is the sum of C(n - 1, i) * a[i] modulo 10 (the pyramid is Pascal's triangle). Modulo 10 = 2 * 5, so
// compute the sum modulo 2 and modulo 5 with Lucas (Theorem 2.3.8), then pick the digit with those two remainders.
int binomMod(int n, int r, int p) {  // C(n, r) mod p for p = 2 or 5, digit by digit
    int res = 1;
    for (; n > 0 || r > 0; n /= p, r /= p) {
        int a = n % p, b = r % p;
        if (b > a) return 0;
        int c = 1;  // C(a, b) exactly, a <= 4; each division is exact
        for (int i = 1; i <= b; i++) c = c * (a - i + 1) / i;
        res = res * c % p;
    }
    return res;
}
int triangularSum(const vector<int>& a) {
    int n = a.size(), s2 = 0, s5 = 0;
    for (int i = 0; i < n; i++) {
        s2 = (s2 + binomMod(n - 1, i, 2) * a[i]) % 2;
        s5 = (s5 + binomMod(n - 1, i, 5) * a[i]) % 5;
    }
    for (int d = 0; d < 10; d++) if (d % 2 == s2 && d % 5 == s5) return d;
    return -1;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << triangularSum(a) << "\n";
}
