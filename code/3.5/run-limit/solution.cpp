/*
Problem: count the strings of length n over an alphabet of k letters in which no letter appears
more than r times in a row, modulo 10^9 + 7.
Input: n k r (1 <= n <= 10^5, 1 <= k <= 26, 1 <= r <= 20).
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.5.2. cnt[j] = the valid strings of the current length whose last run has length j; no letter more than r times
// in a row.
long long runLimit(long long n, long long k, int r) {
    const long long MOD = 1'000'000'007;
    vector<long long> cnt(r + 1, 0);
    cnt[1] = k % MOD;  // length 1: any letter, run length 1
    for (long long len = 2; len <= n; len++) {
        long long total = 0;
        for (int j = 1; j <= r; j++) total = (total + cnt[j]) % MOD;
        vector<long long> next(r + 1, 0);
        next[1] = total * (k - 1) % MOD;                    // a different letter starts a new run
        for (int j = 2; j <= r; j++) next[j] = cnt[j - 1];  // the same letter extends the run
        cnt = next;
    }
    long long answer = 0;
    for (int j = 1; j <= r; j++) answer = (answer + cnt[j]) % MOD;
    return answer;
}
// snippet:end

int main() {
    long long n, k, r;
    cin >> n >> k >> r;
    cout << runLimit(n, k, r) << "\n";
}
