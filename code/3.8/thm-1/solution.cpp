#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.8.1. The tight walk: F(N) = how many x in [0, N] have a digit sum that is a multiple of 4. The state is the digit sum
// mod 4 and the tight flag (is the prefix still equal to N's prefix).
long long countUpTo(long long N) {
    if (N < 0) return 0;
    string digits = to_string(N);
    int L = digits.size();
    vector<array<long long, 4>> memo(L + 1, {-1, -1, -1, -1});  // only states with tight == false
    function<long long(int, int, bool)> go = [&](int pos, int s, bool tight) -> long long {
        if (pos == L) return s == 0;
        if (!tight && memo[pos][s] != -1) return memo[pos][s];
        int hi = tight ? digits[pos] - '0' : 9;
        long long total = 0;
        for (int c = 0; c <= hi; c++) total += go(pos + 1, (s + c) % 4, tight && c == hi);
        if (!tight) memo[pos][s] = total;
        return total;
    };
    return go(0, 0, true);
}
// snippet:end

int main() {
    cout << "F(25) = " << countUpTo(25) << ": the numbers";
    for (int x = 0; x <= 25; x++) {
        int s = 0;
        for (int y = x; y > 0; y /= 10) s += y % 10;
        if (s % 4 == 0) cout << ' ' << x;
    }
    cout << '\n';
    for (long long n = 0; n <= 3000; n++) {
        long long brute = 0;
        for (long long x = 0; x <= n; x++) {
            int s = 0;
            for (long long y = x; y > 0; y /= 10) s += y % 10;
            brute += s % 4 == 0;
        }
        if (n % 37 == 0 && brute != countUpTo(n)) return 1;
    }
}
