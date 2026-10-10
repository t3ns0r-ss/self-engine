#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.4.2. A count is a sum of indicators and E[indicator] = P(event): fixed points of a random permutation
// (n events of probability 1/n) and inversions (n(n-1)/2 pairs, each inverted with probability 1/2).
double expectedFixedPoints(int n) { return n * (1.0 / n); }
double expectedInversions(int n) { return n * (n - 1) / 2 * 0.5; }
// snippet:end

int main() {
    cout << fixed << setprecision(1);
    cout << "fixed points of a random permutation of 4: " << expectedFixedPoints(4) << '\n';
    cout << "inversions of a random permutation of 3: " << expectedInversions(3) << " (total 9 over 6 permutations)\n";
    for (int n = 1; n <= 7; n++) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        double fixedTotal = 0, invTotal = 0, count = 0;
        do {
            count++;
            for (int i = 0; i < n; i++) {
                fixedTotal += p[i] == i;
                for (int j = i + 1; j < n; j++) invTotal += p[i] > p[j];
            }
        } while (next_permutation(p.begin(), p.end()));
        if (fabs(fixedTotal / count - expectedFixedPoints(n)) > 1e-9 || fabs(invTotal / count - expectedInversions(n)) > 1e-9) return 1;
    }
}
