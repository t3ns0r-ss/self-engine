/*
Problem: count the primes in [l, r] for q ranges.
Input: N q (2 <= N <= 10^7, 1 <= q <= 2*10^5), then q lines l r (1 <= l <= r <= N).
Output: for each range, the number of primes p with l <= p <= r.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.1. cnt[x] = the number of primes <= x, from a sieve of Eratosthenes plus prefix sums (topic 1.2).
vector<int> primeCounts(int N) {
    vector<char> composite(N + 1, 0);
    for (int p = 2; (long long)p * p <= N; p++) {
        if (composite[p]) continue;
        for (int j = p * p; j <= N; j += p) composite[j] = 1;
    }
    vector<int> cnt(N + 1, 0);
    for (int x = 2; x <= N; x++) cnt[x] = cnt[x - 1] + (composite[x] ? 0 : 1);
    return cnt;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, q;
    cin >> N >> q;
    vector<int> cnt = primeCounts(N);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << cnt[r] - cnt[l - 1] << "\n";
    }
}
