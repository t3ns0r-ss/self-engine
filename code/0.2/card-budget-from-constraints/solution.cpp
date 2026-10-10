#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: count the pairs i < j for n = 3000 with a double loop. Brute: run the loops. Method: n (n - 1) / 2.
    long long n = 3000, counted = 0;
    for (long long i = 0; i < n; i++)
        for (long long j = i + 1; j < n; j++) counted++;
    cout << "P1 brute=" << counted << " method=" << n * (n - 1) / 2 << '\n';
    // N1: one loop over n = 10^5 elements whose body scans all n elements. Brute: the steps taken.
    // Method: the count of the outer loop alone.
    long long m = 100000, taken = 0;
    for (long long i = 0; i < m; i++) taken += m;
    cout << "N1 brute=" << taken << " method=" << m << '\n';
    // N2: the 12497500 pair steps for n = 5000, but each step is a lookup that costs about 50 simple steps.
    long long pairsSteps = 5000LL * 4999 / 2;
    cout << "N2 brute=" << pairsSteps * 50 << " method=" << pairsSteps << '\n';
}
