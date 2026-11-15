#include <bits/stdc++.h>
using namespace std;

pair<long long, long long> countAndTotal(long long N, bool weighted) {
    string digits = to_string(N);
    int L = digits.size();
    function<pair<long long, long long>(int, bool)> go = [&](int pos, bool tight) -> pair<long long, long long> {
        if (pos == L) return {1, 0};
        long long weight = 1;
        for (int i = pos + 1; i < L; i++) weight *= 10;
        int hi = tight ? digits[pos] - '0' : 9;
        long long count = 0, total = 0;
        for (int c = 0; c <= hi; c++) {
            auto [n, t] = go(pos + 1, tight && c == hi);
            count += n;
            total += t + (weighted ? c * weight : c) * n;
        }
        return {count, total};
    };
    return go(0, true);
}
int main() {
    // P1: the sum of the digit sums of 0..25. Brute: add them. Method: (count, total) per state.
    long long brute = 0;
    for (int x = 0; x <= 25; x++) for (int y = x; y > 0; y /= 10) brute += y % 10;
    cout << "P1 brute=" << brute << " method=" << countAndTotal(25, false).second << '\n';
    // N1: the sum of the numbers 0..25, with a digit adding c instead of c * 10^k to each completion.
    long long sumOfNumbers = 0;
    for (int x = 0; x <= 25; x++) sumOfNumbers += x;
    cout << "N1 brute=" << sumOfNumbers << " method=" << countAndTotal(25, false).second << '\n';
}
