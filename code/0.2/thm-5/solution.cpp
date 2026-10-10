#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.2.5. The steps of the loop over multiples: for each i, the numbers i, 2i, 3i, ... up to n.
long long multipleSteps(int n) {
    long long steps = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i) steps++;
    return steps;
}
// snippet:end

int main() {
    for (int n : {10, 1000, 1000000}) cout << "n = " << n << ": " << multipleSteps(n) << " steps\n";
    for (int n = 1; n <= 3000; n++) {
        double bound = n * (1 + log((double)n));
        long long exact = 0;
        for (int i = 1; i <= n; i++) exact += n / i;
        if (multipleSteps(n) != exact || multipleSteps(n) > bound + 1e-9) return 1;
    }
}
