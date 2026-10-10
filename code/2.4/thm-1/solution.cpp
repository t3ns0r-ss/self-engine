#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.4.1. Linearity: the expected sum of several dice is the sum of the expected values, with no independence needed.
double expectedDie(int sides) { return (sides + 1) / 2.0; }
double expectedSum(const vector<int>& dice) {
    double e = 0;
    for (int s : dice) e += expectedDie(s);
    return e;
}
// snippet:end

int main() {
    cout << fixed << setprecision(1);
    cout << "one die: " << expectedDie(6) << ", two dice: " << expectedSum({6, 6}) << '\n';
    for (int a = 1; a <= 6; a++) for (int b = 1; b <= 6; b++) {
        double total = 0;
        for (int x = 1; x <= a; x++) for (int y = 1; y <= b; y++) total += x + y;
        if (fabs(total / (a * b) - expectedSum({a, b})) > 1e-9) return 1;
    }
}
