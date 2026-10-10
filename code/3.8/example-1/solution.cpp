/*
Problem: AtCoder EDPC S, Digit Sum. Count the integers between 1 and K whose decimal digit sum is a multiple of D,
modulo 10^9 + 7.
Input: K (1 <= K < 10^10000, as a string of digits), then D (1 <= D <= 100).
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// EDPC S. free_[r] = the prefixes already below K's prefix whose digit sum is r mod d; tightSum = K's own prefix sum mod d.
long long digitSumMultiples(const string& k, int d) {
    const long long MOD = 1'000'000'007;
    vector<long long> free_(d, 0);
    int tightSum = 0;
    for (char ch : k) {
        int digit = ch - '0';
        vector<long long> next(d, 0);
        for (int r = 0; r < d; r++) {  // a free prefix takes any digit
            if (free_[r] == 0) continue;
            for (int c = 0; c <= 9; c++) next[(r + c) % d] = (next[(r + c) % d] + free_[r]) % MOD;
        }
        for (int c = 0; c < digit; c++)  // the tight prefix becomes free with a smaller digit
            next[(tightSum + c) % d] = (next[(tightSum + c) % d] + 1) % MOD;
        tightSum = (tightSum + digit) % d;  // or stays tight with K's digit
        free_ = next;
    }
    long long answer = free_[0] + (tightSum == 0);  // numbers below K, plus K itself
    return (answer - 1 + MOD) % MOD;                // 0 was counted (digit sum 0); the range starts at 1
}
// snippet:end

int main() {
    string k;
    int d;
    cin >> k >> d;
    cout << digitSumMultiples(k, d) << "\n";
}
