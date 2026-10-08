/*
Problem: count the primes in [l, r] for q ranges.
Input: N q (2 <= N <= 10^7, 1 <= q <= 2*10^5), then q lines l r (1 <= l <= r <= N).
Output: for each range, the number of primes p with l <= p <= r.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, q;
    cin >> N >> q;
    vector<char> composite(N + 1, 0);
    for (int p = 2; (long long)p * p <= N; p++) {
        if (composite[p]) continue;
        for (int j = p * p; j <= N; j += p) composite[j] = 1;  // Theorem 2.1.1
    }
    vector<int> cnt(N + 1, 0);  // cnt[x] = number of primes <= x (topic 1.2)
    for (int x = 2; x <= N; x++) cnt[x] = cnt[x - 1] + (composite[x] ? 0 : 1);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << cnt[r] - cnt[l - 1] << "\n";
    }
}
