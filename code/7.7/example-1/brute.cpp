#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> f(n + 1, 0);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int d = 1; d <= 6 && d <= i; d++) f[i] = (f[i] + f[i - d]) % 1000000007;
    cout << f[n] << "\n";
}
