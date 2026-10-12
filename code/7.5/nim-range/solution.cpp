#include <bits/stdc++.h>
using namespace std;

/*
Problem: n quarries; the quarry i has m_i heaps of stones of the sizes x_i, x_i + 1, ..., x_i + m_i - 1 (x_i, m_i up to 10^16). Two players take
turns; a move removes any positive number of stones from one heap; the player who cannot move loses. Print "tolik" if the first player wins,
and "bolik" otherwise.
Input: n, then n lines "x m".
Output: tolik or bolik.
*/


// snippet:begin
// Theorem 7.5.2. The xor of all the heap sizes decides. The xor of 0..k is k, 1, k + 1, 0 for k mod 4 = 0, 1, 2, 3, and the xor of the run
// x .. x + m - 1 is the xor of 0..x+m-1 xored with the xor of 0..x-1.
long long xorUpTo(long long k) {
    switch (k % 4) {
        case 0: return k;
        case 1: return 1;
        case 2: return k + 1;
        default: return 0;
    }
}
bool firstWins(const vector<pair<long long, long long>>& quarries) {
    long long total = 0;
    for (auto [x, m] : quarries) total ^= xorUpTo(x + m - 1) ^ xorUpTo(x - 1);
    return total != 0;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> q(n);
    for (auto& [x, m] : q) cin >> x >> m;
    cout << (firstWins(q) ? "tolik" : "bolik") << "\n";
}
