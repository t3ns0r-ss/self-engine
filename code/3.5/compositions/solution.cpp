/*
Problem: count the ways to write n as a sum of allowed parts that use at least one part >= d,
modulo 10^9 + 7. With t = 0, order matters (1 + 2 and 2 + 1 differ); with t = 1 it does not.
Input: t n d m (1 <= n <= 10^5, 1 <= d <= n, 1 <= m <= 100), then m distinct allowed parts (1 <= part <= n).
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 3.5.1 and 3.5.3. The sums of n from the given parts (ordered: totals outside; unordered: parts outside), and
// "at least one part >= d" as all sums minus the sums that use only parts below d.
const long long MOD = 1'000'000'007;
long long countSums(bool ordered, int n, const vector<int>& parts) {
    vector<long long> f(n + 1, 0);
    f[0] = 1;  // the empty sum
    if (ordered) {
        for (int total = 1; total <= n; total++)
            for (int p : parts)
                if (p <= total) f[total] = (f[total] + f[total - p]) % MOD;
    } else {
        for (int p : parts)
            for (int total = p; total <= n; total++) f[total] = (f[total] + f[total - p]) % MOD;
    }
    return f[n];
}
long long atLeastOneBig(bool ordered, int n, int d, const vector<int>& parts) {
    vector<int> small;
    for (int p : parts) if (p < d) small.push_back(p);
    return (countSums(ordered, n, parts) - countSums(ordered, n, small) + MOD) % MOD;
}
// snippet:end

int main() {
    int t, n, d, m;
    cin >> t >> n >> d >> m;
    vector<int> parts(m);
    for (int& p : parts) cin >> p;
    cout << atLeastOneBig(t == 0, n, d, parts) << "\n";
}
