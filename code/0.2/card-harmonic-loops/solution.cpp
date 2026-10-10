#include <bits/stdc++.h>
using namespace std;

long long loopSteps(int n) {
    long long steps = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i) steps++;
    return steps;
}

int main() {
    // P1 and P2: the steps of the loop over multiples. Brute: run it. Method: the sum of floor(n / i).
    for (int n : {10, 1000}) {
        long long formula = 0;
        for (int i = 1; i <= n; i++) formula += n / i;
        cout << (n == 10 ? "P1" : "P2") << " brute=" << loopSteps(n) << " method=" << formula << '\n';
    }
    // N1: the divisors of the single number 10^6. Brute: the steps of the square-root method.
    // Method: the loop over the multiples of every i up to 10^6.
    long long root = 0;
    for (long long d = 1; d * d <= 1000000; d++) root++;
    cout << "N1 brute=" << root << " method=" << loopSteps(1000000) << '\n';
    // N2: for n = 1000, an inner loop that runs j = 1..n and tests j % i == 0 instead of stepping by i.
    long long scanned = 0;
    for (int i = 1; i <= 1000; i++)
        for (int j = 1; j <= 1000; j++) scanned++;
    cout << "N2 brute=" << scanned << " method=" << loopSteps(1000) << '\n';
}
