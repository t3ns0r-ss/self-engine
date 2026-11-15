#include <bits/stdc++.h>
using namespace std;

long long g(long long n, map<long long, long long>& cache) {
    if (n == 0) return 0;
    auto it = cache.find(n);
    if (it != cache.end()) return it->second;
    return cache[n] = max(n, g(n / 2, cache) + g(n / 3, cache) + g(n / 4, cache));
}
long long gPlain(long long n) { return n == 0 ? 0 : max(n, gPlain(n / 2) + gPlain(n / 3) + gPlain(n / 4)); }
long long ways(int i, vector<long long>& cache) {
    if (i <= 1) return 1;
    if (cache[i]) return cache[i];
    return cache[i] = ways(i - 1, cache) + ways(i - 2, cache);
}
long long waysPlain(int i) { return i <= 1 ? 1 : waysPlain(i - 1) + waysPlain(i - 2); }
int main() {
    // P1: the coin exchange value g(12). P2: the ways to climb 20 stairs. Brute: the plain recursion. Method: with a cache.
    map<long long, long long> c;
    cout << "P1 brute=" << gPlain(12) << " method=" << g(12, c) << '\n';
    vector<long long> cache(21, 0);
    cout << "P2 brute=" << waysPlain(20) << " method=" << ways(20, cache) << '\n';
    // N1: f(n) = f(n - 1) + n with f(0) = 0 for n = 10^9; the cache would hold 10^9 values.
    long long n = 1000000000;
    cout << "N1 brute=" << n * (n + 1) / 2 << " method=" << (n > 10000000 ? "too-slow" : "ok") << '\n';
}
