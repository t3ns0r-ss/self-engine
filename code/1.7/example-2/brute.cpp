#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    long long total = 0;
    for (long long k = 0; k <= n; k++) total += __builtin_popcountll(k & m);
    cout << total % 998244353 << "\n";
}
