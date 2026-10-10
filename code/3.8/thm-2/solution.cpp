#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.8.2. Ranges: the count in [A, B] is F(B) - F(A - 1), with F(-1) = 0. F here counts the digit sums that are multiples of 4.
long long countUpTo(long long N) {
    if (N < 0) return 0;
    long long total = 0;
    for (long long x = 0; x <= N; x++) {
        int s = 0;
        for (long long y = x; y > 0; y /= 10) s += y % 10;
        total += s % 4 == 0;
    }
    return total;
}
long long countRange(long long A, long long B) { return countUpTo(B) - countUpTo(A - 1); }
// snippet:end

int main() {
    cout << "[10, 25]: F(25) - F(9) = " << countUpTo(25) << " - " << countUpTo(9) << " = " << countRange(10, 25) << '\n';
    for (long long a = 0; a <= 60; a += 7) for (long long b = a; b <= 120; b += 11) {
        long long brute = 0;
        for (long long x = a; x <= b; x++) {
            int s = 0;
            for (long long y = x; y > 0; y /= 10) s += y % 10;
            brute += s % 4 == 0;
        }
        if (brute != countRange(a, b)) return 1;
    }
}
