#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.3. The sums of a_i xor a_j, a_i and a_j, a_i or a_j over all pairs i < j, from the number c of values with each bit.
array<long long, 3> pairSums(const vector<int>& a) {
    long long n = a.size(), sx = 0, sa = 0, so = 0, pairs = n * (n - 1) / 2;
    for (int b = 0; b < 30; b++) {
        long long c = 0;  // how many values have bit b
        for (int x : a) c += (x >> b) & 1;
        long long w = 1LL << b;
        sx += w * (c * (n - c));                       // exactly one has the bit
        sa += w * (c * (c - 1) / 2);                   // both have it
        so += w * (pairs - (n - c) * (n - c - 1) / 2); // not "neither"
    }
    return {sx, sa, so};
}
// snippet:end

int main() {
    array<long long, 3> r = pairSums({1, 2, 3});
    cout << "1 2 3: sum of XOR " << r[0] << ", AND " << r[1] << ", OR " << r[2] << '\n';
    r = pairSums({5, 5});
    cout << "5 5: sum of XOR " << r[0] << ", AND " << r[1] << ", OR " << r[2] << '\n';
    mt19937 rng(3);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 7;
        vector<int> a(n);
        for (int& x : a) x = rng() % 64;
        array<long long, 3> want = {0, 0, 0};
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) want[0] += a[i] ^ a[j], want[1] += a[i] & a[j], want[2] += a[i] | a[j];
        if (want != pairSums(a)) return 1;
    }
}
