/*
Problem: AtCoder ABC 291 D, Flip Cards. N cards in a row show A_i (front) or B_i (back); count the ways to choose
which cards show their back so that neighbouring cards always show different numbers, modulo 998244353.
Input: N (N <= 2 * 10^5), then N lines A_i B_i.
Output: the number of valid choices modulo 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

int main() {
    int n;
    cin >> n;
    vector<array<long long, 2>> side(n);  // side[i][0] = front value, side[i][1] = back value
    for (auto& c : side) cin >> c[0] >> c[1];
    // ways[s] = number of valid choices for cards 0..i with card i showing side s (Theorem 3.2.5)
    array<long long, 2> ways = {1, 1};  // base case: card 0 alone, either side
    for (int i = 1; i < n; i++) {
        array<long long, 2> next = {0, 0};
        for (int s = 0; s < 2; s++)        // side of card i
            for (int t = 0; t < 2; t++)    // side of card i - 1
                if (side[i][s] != side[i - 1][t]) next[s] = (next[s] + ways[t]) % MOD;
        ways = next;
    }
    cout << (ways[0] + ways[1]) % MOD << "\n";
}
