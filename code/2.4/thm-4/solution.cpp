#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.4.4. E[X] = sum over x >= 1 of P(X >= x). For the maximum of k independent draws from 1..m,
// P(max >= x) = 1 - ((x - 1)/m)^k.
double expectedMax(int m, int k) {
    double e = 0;
    for (int x = 1; x <= m; x++) e += 1 - pow((x - 1.0) / m, k);
    return e;
}
// snippet:end

int main() {
    cout << fixed << setprecision(4);
    cout << "the larger of two dice: " << expectedMax(6, 2) << " = 161/36\n";
    for (int m = 1; m <= 6; m++) for (int k = 1; k <= 3; k++) {
        double total = 0, count = 0;
        int cells = 1;
        for (int i = 0; i < k; i++) cells *= m;
        for (int code = 0; code < cells; code++) {
            int c = code, best = 0;
            for (int i = 0; i < k; i++) best = max(best, c % m + 1), c /= m;
            total += best, count++;
        }
        if (fabs(total / count - expectedMax(m, k)) > 1e-9) return 1;
    }
}
