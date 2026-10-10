#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.4.5. Waiting for a success of probability p takes 1/p trials; stages add. Coupon collector: n * (1 + 1/2 + ... + 1/n).
double waitFor(double p) { return 1 / p; }
double couponCollector(int n) {
    double e = 0;
    for (int j = 0; j < n; j++) e += n / (double)(n - j);  // stage j: a new kind has probability (n - j)/n
    return e;
}
// snippet:end

int main() {
    cout << fixed << setprecision(1);
    cout << "rolls of a die until a 6: " << waitFor(1 / 6.0) << '\n';
    cout << "rolls until all six faces have appeared: " << couponCollector(6) << '\n';
    mt19937 rng(11);
    double total = 0;
    const int trials = 200000;
    for (int t = 0; t < trials; t++) {
        int seen = 0, rolls = 0;
        while (seen != 63) seen |= 1 << (rng() % 6), rolls++;
        total += rolls;
    }
    if (fabs(total / trials - couponCollector(6)) > 0.1) return 1;
}
