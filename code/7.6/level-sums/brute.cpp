#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<long long> f(x + 1, 0);
    f[0] = 1;
    vector<int> d(n);
    for (int& v : d) cin >> v;
    long long total = 0;
    for (int i = 0; i <= x; i++) {
        if (i > 0)
            for (int len : d)
                if (len <= i) f[i] = (f[i] + f[i - len]) % 1000000007;
        total = (total + f[i]) % 1000000007;
    }
    cout << total << "\n";
}
