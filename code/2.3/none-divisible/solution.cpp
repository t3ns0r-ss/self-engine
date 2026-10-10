/*
Problem: count the integers in [1, N] divisible by none of a_1 .. a_m.
Input: N m (1 <= N <= 10^18, 1 <= m <= 15), then a_1 .. a_m (1 <= a_i <= 10^9).
Output: the count (an exact integer, at most N).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.6. The integers in [1, N] divisible by none of a_1..a_m: the alternating sum over the sets S of
// N / lcm(S) (Theorem 0.4.2); an lcm above N counts as N + 1, so its term is 0.
long long noneDivisible(long long N, const vector<long long>& a) {
    int m = a.size();
    long long count = 0;
    for (int S = 0; S < (1 << m); S++) {
        long long l = 1;
        for (int i = 0; i < m && l <= N; i++)
            if (S >> i & 1) {
                long long g = gcd(l, a[i]);
                if ((__int128)(l / g) * a[i] > N) l = N + 1;
                else l = l / g * a[i];
            }
        long long term = N / l;
        count += (__builtin_popcount(S) % 2 == 0) ? term : -term;
    }
    return count;
}
// snippet:end

int main() {
    long long N;
    int m;
    cin >> N >> m;
    vector<long long> a(m);
    for (auto& x : a) cin >> x;
    cout << noneDivisible(N, a) << "\n";
}
