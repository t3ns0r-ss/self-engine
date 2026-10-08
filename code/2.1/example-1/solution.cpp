/*
Problem: AtCoder ABC 177 E, Coprime.
Input: N (2 <= N <= 10^6), then A_1 .. A_N (1 <= A_i <= 10^6).
Output: "pairwise coprime", "setwise coprime" or "not coprime".
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v : a) cin >> v;
    const int M = 1000000;
    vector<int> spf(M + 1, 0);
    for (int p = 2; p <= M; p++) {
        if (spf[p] != 0) continue;
        spf[p] = p;
        if ((long long)p * p > M) continue;
        for (int j = p * p; j <= M; j += p)
            if (spf[j] == 0) spf[j] = p;
    }
    vector<int> used(M + 1, 0);  // used[p] = number of elements divisible by p
    bool pairwise = true;
    int g = 0;
    for (int v : a) {
        g = gcd(g, v);
        while (v > 1) {
            int p = spf[v];
            if (++used[p] == 2) pairwise = false;  // p divides two elements
            while (v % p == 0) v /= p;              // count p once per element
        }
    }
    if (pairwise) cout << "pairwise coprime\n";
    else if (g == 1) cout << "setwise coprime\n";
    else cout << "not coprime\n";
}
