// Brute force: play the match out in every possible order of round winners and add up weight and length of each.
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;
long long power(long long base, long long e) {
    long long r = 1;
    for (base %= MOD; e > 0; e >>= 1, base = base * base % MOD)
        if (e & 1) r = r * base % MOD;
    return r;
}
long long w, lose, probA = 0, expRounds = 0;

void play(int x, int y, long long weight, int rounds) {
    if (x == 0) { probA = (probA + weight) % MOD; expRounds = (expRounds + weight * rounds) % MOD; return; }
    if (y == 0) { expRounds = (expRounds + weight * rounds) % MOD; return; }
    play(x - 1, y, weight * w % MOD, rounds + 1);
    play(x, y - 1, weight * lose % MOD, rounds + 1);
}

int main() {
    int a, b;
    long long num, den;
    cin >> a >> b >> num >> den;
    w = num % MOD * power(den, MOD - 2) % MOD;
    lose = (1 - w + MOD) % MOD;
    play(a, b, 1, 0);
    cout << probA << " " << expRounds << "\n";
}
