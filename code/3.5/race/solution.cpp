/*
Problem: two players A and B play rounds. In each round A wins with probability num / den, otherwise B wins. A needs
a round wins to take the match and B needs b round wins; the match ends as soon as one of them has enough. Print the
probability that A takes the match and the expected number of rounds, both modulo 10^9 + 7.
Input: a b num den (1 <= a, b <= 3000, 1 <= num < den <= 10^9).
Output: two numbers, the probability and the expected number of rounds, each modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;

long long power(long long base, long long e) {
    long long r = 1;
    for (base %= MOD; e > 0; e >>= 1, base = base * base % MOD)
        if (e & 1) r = r * base % MOD;
    return r;
}

// snippet:begin
// Theorem 3.5.5. State (x, y): A still needs x wins, B needs y. P = the probability that A takes the match, E = the expected
// rounds still to play. Both come from the first round: A wins it with probability w, otherwise B does.
pair<long long, long long> race(int a, int b, long long num, long long den) {
    long long w = num % MOD * power(den, MOD - 2) % MOD;  // num / den as a remainder (topic 2.2)
    long long lose = (1 - w + MOD) % MOD;
    vector<vector<long long>> P(a + 1, vector<long long>(b + 1, 0)), E = P;
    for (int y = 1; y <= b; y++) P[0][y] = 1;  // A has enough, B does not: A took the match
    for (int x = 1; x <= a; x++)
        for (int y = 1; y <= b; y++) {
            P[x][y] = (w * P[x - 1][y] + lose * P[x][y - 1]) % MOD;
            E[x][y] = (1 + w * E[x - 1][y] + lose * E[x][y - 1]) % MOD;
        }
    return {P[a][b], E[a][b]};
}
// snippet:end

int main() {
    int a, b;
    long long num, den;
    cin >> a >> b >> num >> den;
    auto [p, e] = race(a, b, num, den);
    cout << p << " " << e << "\n";
}
