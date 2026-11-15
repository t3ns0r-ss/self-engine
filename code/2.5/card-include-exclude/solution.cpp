#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the integers in 1..100 divisible by none of 2, 3, 5. Brute: test each. Method: the alternating sum.
    int brute = 0;
    for (int x = 1; x <= 100; x++) brute += x % 2 && x % 3 && x % 5;
    int method = 100 - (50 + 33 + 20) + (16 + 10 + 6) - 3;
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the permutations of 4 elements with no fixed point. Brute: all 24. Method: sum of (-1)^j C(4, j) (4 - j)!.
    vector<int> p = {0, 1, 2, 3};
    int derangements = 0;
    do {
        bool ok = true;
        for (int i = 0; i < 4; i++) if (p[i] == i) ok = false;
        derangements += ok;
    } while (next_permutation(p.begin(), p.end()));
    cout << "P2 brute=" << derangements << " method=" << 24 - 24 + 12 - 4 + 1 << '\n';
    // N1: the integers in 1..100 divisible by 4 or by 6; N(S) is taken as N / (4 * 6) instead of N / lcm(4, 6) = N / 12.
    int both = 0;
    for (int x = 1; x <= 100; x++) both += x % 4 == 0 || x % 6 == 0;
    cout << "N1 brute=" << both << " method=" << 100 / 4 + 100 / 6 - 100 / (4 * 6) << '\n';
}
