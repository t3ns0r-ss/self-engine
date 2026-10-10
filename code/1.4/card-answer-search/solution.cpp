#include <bits/stdc++.h>
using namespace std;

long long firstTrue(long long L, long long R, const function<bool(long long)>& ok) {
    long long lo = L - 1, hi = R + 1;
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        if (ok(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main() {
    // P1: the smallest x with x * x >= 50. Brute: try x = 1, 2, ... Method: binary search on the answer.
    long long brute = 1;
    while (brute * brute < 50) brute++;
    cout << "P1 brute=" << brute << " method=" << firstTrue(1, 100, [](long long x) { return x * x >= 50; }) << '\n';
    // N1: the smallest x >= 5 that divides 12. "x divides 12" is not monotone, but it is searched as if it were.
    long long bf = 5;
    while (12 % bf != 0) bf++;
    cout << "N1 brute=" << bf << " method=" << firstTrue(5, 12, [](long long x) { return 12 % x == 0; }) << '\n';
    // N2: the smallest x with x * x >= 10^18, searched in 1..10^6 only.
    cout << "N2 brute=" << 1000000000LL << " method=" << firstTrue(1, 1000000, [](long long x) { return x * x >= 1000000000000000000LL; }) << '\n';
}
