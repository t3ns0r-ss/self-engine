#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    int m;
    cin >> n >> m;
    vector<long long> f(n + 1);
    f[0] = 1;
    for (int i = 1; i <= n; i++) f[i] = (f[i - 1] + (i >= m ? f[i - m] : 0)) % 1000000007;
    cout << f[n] << "\n";
}
