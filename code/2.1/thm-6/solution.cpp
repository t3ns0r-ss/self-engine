#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.6. c[d] = elements divisible by d; E[d] = pairs with gcd exactly d, computed from d = M down to 1.
vector<long long> exactGcdPairs(const vector<int>& a, int M) {
    vector<long long> cnt(M + 1, 0), E(M + 1, 0);
    for (int v : a) cnt[v]++;
    for (int d = M; d >= 1; d--) {
        long long c = 0;
        for (int k = d; k <= M; k += d) c += cnt[k];
        E[d] = c * (c - 1) / 2;                            // pairs with d dividing both
        for (int k = 2 * d; k <= M; k += d) E[d] -= E[k];  // minus those with gcd 2d, 3d, ...
    }
    return E;
}
// snippet:end

int main() {
    vector<int> a = {2, 4, 6, 3};
    auto E = exactGcdPairs(a, 6);
    cout << "a = 2 4 6 3, pairs with gcd exactly d:";
    for (int d = 1; d <= 6; d++) cout << " E[" << d << "]=" << E[d];
    cout << '\n';
    mt19937 rng(7);
    for (int round = 0; round < 200; round++) {
        int n = 2 + rng() % 8, M = 1 + rng() % 30;
        vector<int> b(n);
        for (int& v : b) v = 1 + rng() % M;
        auto F = exactGcdPairs(b, M);
        vector<long long> brute(M + 1, 0);
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) brute[__gcd(b[i], b[j])]++;
        if (F != brute) return 1;
    }
}
