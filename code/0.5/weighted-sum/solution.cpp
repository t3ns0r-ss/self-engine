/*
Problem: count triples (x, y, z) of integers with 0 <= x, y, z <= K and x + 2y + 3z = S.
Input: K S (0 <= K <= 3000, 0 <= S <= 6K).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k, s;
    cin >> k >> s;
    long long count = 0;
    for (long long y = 0; y <= k; y++)
        for (long long z = 0; z <= k; z++) {
            long long x = s - 2 * y - 3 * z;  // x is determined by y and z: no third loop
            if (0 <= x && x <= k) count++;
        }
    cout << count << "\n";
}
