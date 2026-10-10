#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.8.4. Count and total together: each state returns (number of completions, sum of the digit sums over them); putting digit c
// in front adds c to each of the n completions.
pair<long long, long long> countAndTotal(long long N) {
    string digits = to_string(N);
    int L = digits.size();
    function<pair<long long, long long>(int, bool)> go = [&](int pos, bool tight) -> pair<long long, long long> {
        if (pos == L) return {1, 0};
        int hi = tight ? digits[pos] - '0' : 9;
        long long count = 0, total = 0;
        for (int c = 0; c <= hi; c++) {
            auto [n, t] = go(pos + 1, tight && c == hi);
            count += n;
            total += t + c * n;
        }
        return {count, total};
    };
    return go(0, true);
}
// snippet:end

int main() {
    auto [count, total] = countAndTotal(25);
    cout << "numbers 0..25: " << count << ", sum of their digit sums " << total << '\n';
    for (long long n = 0; n <= 2000; n += 17) {
        long long brute = 0;
        for (long long x = 0; x <= n; x++) for (long long y = x; y > 0; y /= 10) brute += y % 10;
        if (countAndTotal(n).second != brute || countAndTotal(n).first != n + 1) return 1;
    }
}
