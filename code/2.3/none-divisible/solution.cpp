/*
Problem: count the integers in [1, N] divisible by none of a_1 .. a_m.
Input: N m (1 <= N <= 10^18, 1 <= m <= 15), then a_1 .. a_m (1 <= a_i <= 10^9).
Output: the count (an exact integer, at most N).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N;
    int m;
    cin >> N >> m;
    vector<long long> a(m);
    for (auto& x : a) cin >> x;
    long long count = 0;
    for (int S = 0; S < (1 << m); S++) {  // every set S of properties (topic 0.5)
        long long l = 1;                     // lcm of the a_i in S, or N + 1 once it exceeds N
        for (int i = 0; i < m && l <= N; i++)
            if (S >> i & 1) {
                long long g = gcd(l, a[i]);
                if ((__int128)(l / g) * a[i] > N) l = N + 1;
                else l = l / g * a[i];
            }
        long long term = N / l;              // numbers divisible by every a_i in S (Theorem 0.4.2)
        count += (__builtin_popcount(S) % 2 == 0) ? term : -term;  // Theorem 2.3.6
    }
    cout << count << "\n";
}
