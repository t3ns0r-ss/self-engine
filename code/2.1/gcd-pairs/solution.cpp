/*
Problem: count the pairs with GCD exactly 1, and find the largest GCD of a pair.
Input: n (2 <= n <= 2*10^5), then a_1 .. a_n (1 <= a_i <= 10^6).
Output: the number of pairs i < j with gcd(a_i, a_j) = 1, and the largest gcd(a_i, a_j).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.6. The number of pairs with gcd exactly d, for every d, by "divisible by d" minus the multiples of d.
// Returns {pairs with gcd 1, the largest gcd of a pair}.
pair<long long, int> gcdPairs(const vector<int>& a) {
    int M = *max_element(a.begin(), a.end());
    vector<long long> cnt(M + 1, 0), E(M + 1, 0);
    for (int v : a) cnt[v]++;
    int best = 1;
    for (int d = M; d >= 1; d--) {
        long long c = 0;  // elements divisible by d
        for (int k = d; k <= M; k += d) c += cnt[k];
        E[d] = c * (c - 1) / 2;  // pairs with d dividing both ...
        for (int k = 2 * d; k <= M; k += d) E[d] -= E[k];  // ... minus those with GCD 2d, 3d, ...
        if (c >= 2 && best == 1) best = d;  // first d from the top shared by two elements
    }
    return {E[1], best};
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v : a) cin >> v;
    auto [coprime, best] = gcdPairs(a);
    cout << coprime << " " << best << "\n";
}
