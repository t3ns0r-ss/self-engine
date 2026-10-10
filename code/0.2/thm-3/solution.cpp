#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.2.3. a + (a + d) + ... + (a + (n - 1) d), and the number of pairs among n items.
// The product is always even: multiply first, then halve.
long long arithSum(long long a, long long d, long long n) { return n * (2 * a + (n - 1) * d) / 2; }
long long pairs(long long n) { return n * (n - 1) / 2; }
// snippet:end

int main() {
    for (auto [a, d, n] : {tuple{1, 1, 5}, tuple{3, 2, 4}, tuple{10, -3, 4}})
        cout << "a = " << a << ", d = " << d << ", n = " << n << ": sum " << arithSum(a, d, n) << '\n';
    cout << "pairs among 5 items: " << pairs(5) << '\n';
    for (int a = -5; a <= 5; a++)
        for (int d = -5; d <= 5; d++)
            for (int n = 1; n <= 20; n++) {
                long long loop = 0;
                for (int k = 0; k < n; k++) loop += a + (long long)k * d;
                if (loop != arithSum(a, d, n)) return 1;
            }
    for (int n = 1; n <= 30; n++) {
        int count = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) count++;
        if (count != pairs(n)) return 1;
    }
}
