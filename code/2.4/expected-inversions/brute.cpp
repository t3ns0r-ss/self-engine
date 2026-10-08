#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 998244353;
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    long long total = 0, perms = 0;
    do {  // every order of the positions, all equally likely
        perms++;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) total += a[idx[i]] > a[idx[j]];
    } while (next_permutation(idx.begin(), idx.end()));
    long long g = gcd(total, perms);
    total /= g, perms /= g;
    long long inv = 1;  // perms^(-1) by Fermat, perms is small and below MOD
    for (long long e = MOD - 2, b = perms % MOD; e > 0; e >>= 1, b = b * b % MOD)
        if (e & 1) inv = inv * b % MOD;
    cout << total % MOD * inv % MOD << "\n";
}
