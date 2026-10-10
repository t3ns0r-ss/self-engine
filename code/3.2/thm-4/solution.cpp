#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.4. Memoisation: the plain recursion makes C(i) = 1 + C(i-1) + C(i-2) calls; with a cache each state is computed once.
long long ways(int i, vector<long long>& cache) {
    if (i <= 1) return 1;
    if (cache[i] != 0) return cache[i];  // computed before: return at once
    return cache[i] = ways(i - 1, cache) + ways(i - 2, cache);
}
// snippet:end

int main() {
    vector<long long> calls(41);
    calls[0] = calls[1] = 1;
    for (int i = 2; i <= 40; i++) calls[i] = 1 + calls[i - 1] + calls[i - 2];
    vector<long long> cache(41, 0);
    long long result = ways(40, cache);
    long long states = 0;
    for (long long c : cache) states += c != 0;
    cout << "40 stairs: " << result << " ways; the plain recursion makes " << calls[40] << " calls, the cache holds " << states << " values\n";
    for (int i = 0; i <= 20; i++) {
        vector<long long> c(i + 2, 0);
        long long a = 1, b = 1;
        for (int j = 2; j <= i; j++) { long long t = a + b; a = b; b = t; }
        if (ways(i, c) != (i == 0 ? 1 : b)) return 1;
    }
}
