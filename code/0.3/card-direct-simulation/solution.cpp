#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: states 0..3 with next = 1 2 3 1, start 0, T = 5. Brute: step 5 times. Method: cycle (mu = 1, lambda = 3).
    vector<int> nxt = {1, 2, 3, 1};
    int s = 0;
    for (int i = 0; i < 5; i++) s = nxt[s];
    vector<int> order = {0, 1, 2, 3};
    long long mu = 1, lambda = 3, T = 5;
    cout << "P1 brute=" << s << " method=" << order[mu + (T - mu) % lambda] << '\n';
    // N1: x -> x + 1 from 0 for T = 10^18 steps. Brute: the closed rule x = T. Method: the 10^8 steps that fit the budget.
    long long x = 0, T2 = 1000000000000000000LL, budget = 100000000;
    for (long long i = 0; i < budget; i++) x++;
    cout << "N1 brute=" << T2 << " method=" << x << '\n';
    // N2: position p -> (p + t) % 5 at step t, from 0, T = 4. Brute: step by step. Method: cycle detection on the
    // position alone, which sees the position 0 twice in a row and concludes that the process stays at 0.
    long long p = 0;
    for (long long t = 0; t < 4; t++) p = (p + t) % 5;
    cout << "N2 brute=" << p << " method=" << 0 << '\n';
}
