/*
Problem: count triples (x, y, z) of integers with 0 <= x, y, z <= K and x + 2y + 3z = S.
Input: K S (0 <= K <= 3000, 0 <= S <= 6K).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.5.1. Triples (x, y, z) with 0 <= x, y, z <= k and x + 2y + 3z = s. x is determined by y and z: no third loop.
long long countTriples(long long k, long long s) {
    long long count = 0;
    for (long long y = 0; y <= k; y++)
        for (long long z = 0; z <= k; z++) {
            long long x = s - 2 * y - 3 * z;
            if (0 <= x && x <= k) count++;
        }
    return count;
}
// snippet:end

int main() {
    long long k, s;
    cin >> k >> s;
    cout << countTriples(k, s) << "\n";
}
