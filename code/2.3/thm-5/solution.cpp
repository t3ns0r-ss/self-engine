#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.5. Solutions of x_1 + ... + x_k = n with x_i >= l_i: C(n - L + k - 1, k - 1), L = sum of the l_i.
long long binomial(long long n, long long r) {
    if (r < 0 || r > n) return 0;
    long long ways = 1;
    for (long long i = 1; i <= r; i++) ways = ways * (n - r + i) / i;
    return ways;
}
long long starsBars(long long n, int k, long long L) {
    if (L > n) return 0;
    return binomial(n - L + k - 1, k - 1);
}
// snippet:end

long long brute(int n, int k, const vector<int>& l, int i = 0) {
    if (i == k) return n == 0;
    long long ways = 0;
    for (int x = l[i]; x <= n; x++) ways += brute(n - x, k, l, i + 1);
    return ways;
}
int main() {
    cout << "7 candies, 3 children: " << starsBars(7, 3, 0) << "; at least one each: " << starsBars(7, 3, 3) << '\n';
    mt19937 rng(3);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 12, k = 1 + rng() % 4;
        vector<int> l(k);
        long long L = 0;
        for (int& x : l) x = rng() % 3, L += x;
        if (brute(n, k, l) != starsBars(n, k, L)) return 1;
    }
}
