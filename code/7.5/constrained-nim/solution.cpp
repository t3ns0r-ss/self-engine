#include <bits/stdc++.h>
using namespace std;

/*
Problem: N piles of stones with A_i stones (N up to 2·10^5, A_i up to 10^9), and numbers L <= R. A move removes between L and R stones
(both included) from one pile, if the pile has at least L stones. The player who cannot move loses; Takahashi moves first.
Print First if Takahashi wins and Second otherwise.
Input: N, L and R, then the N numbers.
Output: First or Second.
*/


// snippet:begin
// Theorem 7.5.3: one pile is a heap with the removals L..R; its Grundy value is floor((A mod (L + R)) / L). The piles are independent, so
// the first player wins exactly when the xor of these values is not 0.
string winner(const vector<long long>& piles, long long L, long long R) {
    long long total = 0;
    for (long long a : piles) total ^= a % (L + R) / L;
    return total ? "First" : "Second";
}
// snippet:end

int main() {
    int n;
    long long L, R;
    cin >> n >> L >> R;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << winner(a, L, R) << "\n";
}
