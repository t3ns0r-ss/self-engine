#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long cnt = 0, sum = 0;
    for (long long d = 1; d <= n; d++)
        if (n % d == 0) cnt++, sum += d;
    vector<pair<long long, int>> f;
    long long m = n;
    for (long long p = 2; p <= m; p++) {
        bool prime = true;
        for (long long q = 2; q < p; q++)
            if (p % q == 0) prime = false;
        if (!prime || m % p != 0) continue;
        int e = 0;
        while (m % p == 0) m /= p, e++;
        f.push_back({p, e});
    }
    for (int i = 0; i < (int)f.size(); i++)
        cout << f[i].first << "^" << f[i].second << (i + 1 < (int)f.size() ? ' ' : '\n');
    cout << cnt << " " << sum << "\n";
}
