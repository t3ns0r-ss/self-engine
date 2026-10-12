#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> d(n);
    for (int& x : d) cin >> x;
    vector<int> ea(n - 1), eb(n - 1);
    vector<long long> w(n - 1);
    for (int i = 0; i + 1 < n; i++) cin >> ea[i] >> eb[i] >> w[i], ea[i]--, eb[i]--;
    long long best = LLONG_MIN;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {
        vector<int> used(n, 0);
        long long sum = 0;
        for (int i = 0; i + 1 < n; i++)
            if (mask >> i & 1) used[ea[i]]++, used[eb[i]]++, sum += w[i];
        bool ok = true;
        for (int v = 0; v < n; v++) ok = ok && used[v] <= d[v];
        if (ok) best = max(best, sum);
    }
    cout << best << "\n";
}
