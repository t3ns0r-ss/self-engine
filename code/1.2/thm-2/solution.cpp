#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.2. Subarrays with sum exactly K, and with sum divisible by m: count earlier equal prefix values.
long long countSumK(const vector<long long>& a, long long K) {
    map<long long, int> seen;
    seen[0] = 1;  // P_0 = 0
    long long P = 0, count = 0;
    for (long long x : a) {
        P += x;
        auto it = seen.find(P - K);
        if (it != seen.end()) count += it->second;  // earlier P_i = P_j - K
        seen[P]++;
    }
    return count;
}

long long countDivisible(const vector<long long>& a, long long m) {
    map<long long, int> seen;
    seen[0] = 1;
    long long P = 0, count = 0;
    for (long long x : a) {
        P += x;
        long long r = (P % m + m) % m;  // P may be negative
        count += seen[r];
        seen[r]++;
    }
    return count;
}
// snippet:end

int main() {
    cout << "1 2 -1 2, sum 3: " << countSumK({1, 2, -1, 2}, 3) << " subarrays\n";
    cout << "1 2 3, sum divisible by 3: " << countDivisible({1, 2, 3}, 3) << " subarrays\n";
    cout << "-1 2 1, sum divisible by 2: " << countDivisible({-1, 2, 1}, 2) << " subarrays\n";
    mt19937 rng(2);
    for (int round = 0; round < 400; round++) {
        int n = rng() % 8 + 1;
        vector<long long> b(n);
        for (auto& x : b) x = (long long)(rng() % 9) - 4;
        long long K = (long long)(rng() % 7) - 3, m = rng() % 4 + 1, c1 = 0, c2 = 0;
        for (int l = 0; l < n; l++) for (int r = l; r < n; r++) {
            long long s = 0;
            for (int i = l; i <= r; i++) s += b[i];
            c1 += s == K;
            c2 += s % m == 0;
        }
        if (c1 != countSumK(b, K) || c2 != countDivisible(b, m)) return 1;
    }
}
