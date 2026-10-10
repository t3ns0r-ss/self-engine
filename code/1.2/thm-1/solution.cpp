#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.1. P[k] = sum of the first k elements; the sum of a[l..r] (0-based) is P[r + 1] - P[l].
vector<long long> prefixSums(const vector<long long>& a) {
    vector<long long> P(a.size() + 1, 0);
    for (int i = 0; i < (int)a.size(); i++) P[i + 1] = P[i] + a[i];
    return P;
}
long long rangeSum(const vector<long long>& P, int l, int r) { return P[r + 1] - P[l]; }
// snippet:end

int main() {
    vector<long long> a = {3, 5, 1, 4}, P = prefixSums(a);
    cout << "a = 3 5 1 4: prefix sums";
    for (long long x : P) cout << ' ' << x;
    cout << '\n';
    cout << "sum of a[1..2]: " << rangeSum(P, 1, 2) << '\n';
    cout << "sum of a[0..3]: " << rangeSum(P, 0, 3) << '\n';
    mt19937 rng(1);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 8 + 1;
        vector<long long> b(n);
        for (auto& x : b) x = (long long)(rng() % 21) - 10;
        vector<long long> Q = prefixSums(b);
        for (int l = 0; l < n; l++) for (int r = l; r < n; r++) {
            long long s = 0;
            for (int i = l; i <= r; i++) s += b[i];
            if (s != rangeSum(Q, l, r)) return 1;
        }
    }
}
