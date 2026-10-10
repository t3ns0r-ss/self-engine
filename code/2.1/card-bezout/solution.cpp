#include <bits/stdc++.h>
using namespace std;

vector<bool> sieve(int N) {
    vector<bool> isPrime(N + 1, true);
    isPrime[0] = false;
    if (N >= 1) isPrime[1] = false;
    for (int p = 2; (long long)p * p <= N; p++)
        if (isPrime[p]) for (int j = p * p; j <= N; j += p) isPrime[j] = false;
    return isPrime;
}
int divisorsBrute(long long n) {
    int c = 0;
    for (long long d = 1; d <= n; d++) c += n % d == 0;
    return c;
}
long long ext(long long a, long long b, long long& x, long long& y) {
    if (b == 0) { x = 1, y = 0; return a; }
    long long x1, y1, g = ext(b, a % b, x1, y1);
    x = y1, y = x1 - (a / b) * y1;
    return g;
}
string smallestX(long long a, long long b, long long c) {
    long long x, y, g = ext(a, b, x, y);
    if (c % g) return "-1";
    long long m = b / g;
    return to_string(((x % m + m) % m) * ((c / g) % m) % m);
}
string smallestBrute(long long a, long long b, long long c) {
    for (long long x = 0; x <= 1000; x++)
        for (long long y = -1000; y <= 1000; y++) if (a * x + b * y == c) return to_string(x);
    return "-1";
}
int main() {
    // P1: 12x + 18y = 30 with the smallest x >= 0. P2: 12x + 18y = 7. Brute: search. Method: extended Euclid.
    cout << "P1 brute=" << smallestBrute(12, 18, 30) << " method=" << smallestX(12, 18, 30) << '\n';
    cout << "P2 brute=" << smallestBrute(12, 18, 7) << " method=" << smallestX(12, 18, 7) << '\n';
    // N1: the fewest coins of values 4 and 5 that make 11 (x, y >= 0). Bezout says the equation is solvable.
    int bruteCoins = -1;
    for (int x = 0; x <= 11; x++) for (int y = 0; y <= 11; y++) if (4 * x + 5 * y == 11) bruteCoins = x + y;
    long long x, y;
    string method = 11 % ext(4, 5, x, y) == 0 ? "solvable" : "unsolvable";
    cout << "N1 brute=" << bruteCoins << " method=" << method << '\n';
}
