/*
Problem: AtCoder ABC 177 E, Coprime.
Input: N (2 <= N <= 10^6), then A_1 .. A_N (1 <= A_i <= 10^6).
Output: "pairwise coprime", "setwise coprime" or "not coprime".
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.4. spf[x] = the smallest prime factor of x, for 2 <= x <= N.
vector<int> buildSpf(int N) {
    vector<int> spf(N + 1, 0);
    for (int p = 2; p <= N; p++) {
        if (spf[p] != 0) continue;  // p is prime
        spf[p] = p;
        if ((long long)p * p > N) continue;
        for (int j = p * p; j <= N; j += p)
            if (spf[j] == 0) spf[j] = p;
    }
    return spf;
}
// "pairwise coprime", "setwise coprime" or "not coprime": a prime dividing two elements breaks pairwise coprimality.
string coprimeKind(const vector<int>& a) {
    vector<int> spf = buildSpf(1000000);
    vector<int> used(1000001, 0);  // used[p] = number of elements divisible by p
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
    if (pairwise) return "pairwise coprime";
    return g == 1 ? "setwise coprime" : "not coprime";
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v : a) cin >> v;
    cout << coprimeKind(a) << "\n";
}
